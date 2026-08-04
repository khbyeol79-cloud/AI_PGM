#include "mainwindow.h"

#include <QAbstractItemView>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QDate>
#include <QDir>
#include <QFile>
#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QStatusBar>
#include <QTableWidget>
#include <QVBoxLayout>

namespace
{
constexpr int IdColumn = 0;
constexpr int TitleColumn = 1;
constexpr int AuthorColumn = 2;
constexpr int PublisherColumn = 3;
constexpr int StatusColumn = 4;
constexpr int BorrowerColumn = 5;
constexpr int DateColumn = 6;
constexpr int BookIndexRole = Qt::UserRole;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    const QString dataDirectory =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDirectory);
    dataFilePath_ = QDir(dataDirectory).filePath("books.json");

    buildUi();
    connectSignals();
    loadFromFile();
    refreshTable();

    showStatus(QString("저장 파일: %1").arg(QDir::toNativeSeparators(dataFilePath_)));
}

void MainWindow::buildUi()
{
    setWindowTitle("도서관리 프로그램");
    resize(1100, 680);
    setMinimumSize(850, 540);

    auto *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(16, 16, 16, 12);
    mainLayout->setSpacing(12);

    auto *registrationGroup = new QGroupBox("도서 등록", central);
    auto *registrationLayout = new QHBoxLayout(registrationGroup);
    auto *formLayout = new QFormLayout;

    idEdit_ = new QLineEdit(registrationGroup);
    titleEdit_ = new QLineEdit(registrationGroup);
    authorEdit_ = new QLineEdit(registrationGroup);
    publisherEdit_ = new QLineEdit(registrationGroup);

    idEdit_->setPlaceholderText("예: B001 또는 ISBN");
    titleEdit_->setPlaceholderText("도서명을 입력하세요");
    authorEdit_->setPlaceholderText("저자를 입력하세요");
    publisherEdit_->setPlaceholderText("출판사를 입력하세요");

    formLayout->addRow("도서번호 *", idEdit_);
    formLayout->addRow("도서명 *", titleEdit_);
    formLayout->addRow("저자 *", authorEdit_);
    formLayout->addRow("출판사", publisherEdit_);

    auto *registrationButtons = new QVBoxLayout;
    addButton_ = new QPushButton("도서 등록", registrationGroup);
    clearButton_ = new QPushButton("입력 지우기", registrationGroup);
    addButton_->setMinimumHeight(38);
    clearButton_->setMinimumHeight(34);
    registrationButtons->addWidget(addButton_);
    registrationButtons->addWidget(clearButton_);
    registrationButtons->addStretch();

    registrationLayout->addLayout(formLayout, 1);
    registrationLayout->addLayout(registrationButtons);
    mainLayout->addWidget(registrationGroup);

    auto *searchLayout = new QHBoxLayout;
    auto *searchLabel = new QLabel("도서 검색", central);
    searchEdit_ = new QLineEdit(central);
    searchEdit_->setClearButtonEnabled(true);
    searchEdit_->setPlaceholderText("도서번호, 도서명, 저자 또는 출판사 검색");
    countLabel_ = new QLabel(central);
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit_, 1);
    searchLayout->addWidget(countLabel_);
    mainLayout->addLayout(searchLayout);

    table_ = new QTableWidget(central);
    table_->setColumnCount(7);
    table_->setHorizontalHeaderLabels(
        {"도서번호", "도서명", "저자", "출판사", "상태", "대출자", "대출일"});
    table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_->setSelectionMode(QAbstractItemView::SingleSelection);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_->setAlternatingRowColors(true);
    table_->setSortingEnabled(true);
    table_->verticalHeader()->setVisible(false);
    table_->horizontalHeader()->setSectionResizeMode(IdColumn, QHeaderView::ResizeToContents);
    table_->horizontalHeader()->setSectionResizeMode(TitleColumn, QHeaderView::Stretch);
    table_->horizontalHeader()->setSectionResizeMode(AuthorColumn, QHeaderView::ResizeToContents);
    table_->horizontalHeader()->setSectionResizeMode(PublisherColumn, QHeaderView::ResizeToContents);
    table_->horizontalHeader()->setSectionResizeMode(StatusColumn, QHeaderView::ResizeToContents);
    table_->horizontalHeader()->setSectionResizeMode(BorrowerColumn, QHeaderView::ResizeToContents);
    table_->horizontalHeader()->setSectionResizeMode(DateColumn, QHeaderView::ResizeToContents);
    mainLayout->addWidget(table_, 1);

    auto *actionLayout = new QHBoxLayout;
    loanButton_ = new QPushButton("선택 도서 대출", central);
    returnButton_ = new QPushButton("선택 도서 반납", central);
    deleteButton_ = new QPushButton("선택 도서 삭제", central);
    saveButton_ = new QPushButton("파일 저장", central);

    for (QPushButton *button : {loanButton_, returnButton_, deleteButton_, saveButton_})
        button->setMinimumHeight(38);

    actionLayout->addWidget(loanButton_);
    actionLayout->addWidget(returnButton_);
    actionLayout->addWidget(deleteButton_);
    actionLayout->addStretch();
    actionLayout->addWidget(saveButton_);
    mainLayout->addLayout(actionLayout);

    setCentralWidget(central);
    statusBar()->setSizeGripEnabled(false);
}

void MainWindow::connectSignals()
{
    connect(addButton_, &QPushButton::clicked, this, &MainWindow::addBook);
    connect(clearButton_, &QPushButton::clicked, this, &MainWindow::clearInputs);
    connect(searchEdit_, &QLineEdit::textChanged, this, &MainWindow::searchBooks);
    connect(loanButton_, &QPushButton::clicked, this, &MainWindow::loanBook);
    connect(returnButton_, &QPushButton::clicked, this, &MainWindow::returnBook);
    connect(deleteButton_, &QPushButton::clicked, this, &MainWindow::deleteBook);
    connect(saveButton_, &QPushButton::clicked, this, [this] { saveToFile(true); });
    connect(publisherEdit_, &QLineEdit::returnPressed, this, &MainWindow::addBook);
}

void MainWindow::addBook()
{
    const QString id = idEdit_->text().trimmed();
    const QString title = titleEdit_->text().trimmed();
    const QString author = authorEdit_->text().trimmed();
    const QString publisher = publisherEdit_->text().trimmed();

    if (id.isEmpty() || title.isEmpty() || author.isEmpty()) {
        QMessageBox::warning(this, "입력 확인", "도서번호, 도서명, 저자는 필수 입력 항목입니다.");
        return;
    }

    if (idExists(id)) {
        QMessageBox::warning(this, "중복 도서번호", "이미 등록된 도서번호입니다.");
        idEdit_->setFocus();
        idEdit_->selectAll();
        return;
    }

    books_.append({id, title, author, publisher, false, {}, {}});
    saveToFile();
    clearInputs();
    refreshTable();
    showStatus(QString("'%1' 도서를 등록하고 저장했습니다.").arg(title));
}

void MainWindow::searchBooks()
{
    refreshTable();
}

void MainWindow::loanBook()
{
    const int index = selectedBookIndex();
    if (index < 0) {
        QMessageBox::information(this, "도서 선택", "대출할 도서를 목록에서 선택하세요.");
        return;
    }

    Book &book = books_[index];
    if (book.borrowed) {
        QMessageBox::warning(this, "대출 불가",
                             QString("이미 %1 님이 대출한 도서입니다.").arg(book.borrower));
        return;
    }

    bool accepted = false;
    const QString borrower = QInputDialog::getText(
        this, "도서 대출", QString("'%1' 도서의 대출자 이름을 입력하세요.").arg(book.title),
        QLineEdit::Normal, {}, &accepted).trimmed();

    if (!accepted)
        return;
    if (borrower.isEmpty()) {
        QMessageBox::warning(this, "입력 확인", "대출자 이름을 입력해야 합니다.");
        return;
    }

    book.borrowed = true;
    book.borrower = borrower;
    book.borrowedDate = QDate::currentDate().toString(Qt::ISODate);
    saveToFile();
    refreshTable();
    showStatus(QString("'%1' 도서를 %2 님에게 대출했습니다.").arg(book.title, borrower));
}

void MainWindow::returnBook()
{
    const int index = selectedBookIndex();
    if (index < 0) {
        QMessageBox::information(this, "도서 선택", "반납할 도서를 목록에서 선택하세요.");
        return;
    }

    Book &book = books_[index];
    if (!book.borrowed) {
        QMessageBox::information(this, "반납 확인", "현재 대출 중인 도서가 아닙니다.");
        return;
    }

    const QString title = book.title;
    book.borrowed = false;
    book.borrower.clear();
    book.borrowedDate.clear();
    saveToFile();
    refreshTable();
    showStatus(QString("'%1' 도서를 반납 처리했습니다.").arg(title));
}

void MainWindow::deleteBook()
{
    const int index = selectedBookIndex();
    if (index < 0) {
        QMessageBox::information(this, "도서 선택", "삭제할 도서를 목록에서 선택하세요.");
        return;
    }

    const Book &book = books_[index];
    if (book.borrowed) {
        QMessageBox::warning(this, "삭제 불가", "대출 중인 도서는 반납 후 삭제할 수 있습니다.");
        return;
    }

    if (QMessageBox::question(
            this, "도서 삭제",
            QString("'%1' 도서를 정말 삭제하시겠습니까?").arg(book.title),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    const QString title = book.title;
    books_.removeAt(index);
    saveToFile();
    refreshTable();
    showStatus(QString("'%1' 도서를 삭제했습니다.").arg(title));
}

void MainWindow::clearInputs()
{
    idEdit_->clear();
    titleEdit_->clear();
    authorEdit_->clear();
    publisherEdit_->clear();
    idEdit_->setFocus();
}

void MainWindow::refreshTable()
{
    const QString keyword = searchEdit_->text().trimmed();
    table_->setSortingEnabled(false);
    table_->setRowCount(0);

    int visibleCount = 0;
    for (int index = 0; index < books_.size(); ++index) {
        const Book &book = books_[index];
        const bool matches = keyword.isEmpty()
            || book.id.contains(keyword, Qt::CaseInsensitive)
            || book.title.contains(keyword, Qt::CaseInsensitive)
            || book.author.contains(keyword, Qt::CaseInsensitive)
            || book.publisher.contains(keyword, Qt::CaseInsensitive);

        if (!matches)
            continue;

        const int row = table_->rowCount();
        table_->insertRow(row);

        auto *idItem = new QTableWidgetItem(book.id);
        idItem->setData(BookIndexRole, index);
        table_->setItem(row, IdColumn, idItem);
        table_->setItem(row, TitleColumn, new QTableWidgetItem(book.title));
        table_->setItem(row, AuthorColumn, new QTableWidgetItem(book.author));
        table_->setItem(row, PublisherColumn, new QTableWidgetItem(book.publisher));
        table_->setItem(row, StatusColumn,
                        new QTableWidgetItem(book.borrowed ? "대출 중" : "대출 가능"));
        table_->setItem(row, BorrowerColumn, new QTableWidgetItem(book.borrower));
        table_->setItem(row, DateColumn, new QTableWidgetItem(book.borrowedDate));
        ++visibleCount;
    }

    table_->setSortingEnabled(true);
    countLabel_->setText(QString("검색 결과 %1권 / 전체 %2권").arg(visibleCount).arg(books_.size()));
}

void MainWindow::loadFromFile()
{
    QFile file(dataFilePath_);
    if (!file.exists())
        return;

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "파일 열기 실패",
                             QString("저장 파일을 열 수 없습니다.\n%1").arg(file.errorString()));
        return;
    }

    QJsonParseError error;
    const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);
    if (error.error != QJsonParseError::NoError || !document.isArray()) {
        QMessageBox::warning(this, "파일 형식 오류",
                             QString("저장 파일의 JSON 형식이 올바르지 않습니다.\n%1")
                                 .arg(error.errorString()));
        return;
    }

    books_.clear();
    for (const QJsonValue &value : document.array()) {
        if (value.isObject())
            books_.append(Book::fromJson(value.toObject()));
    }
}

bool MainWindow::saveToFile(bool showMessage)
{
    QFile file(dataFilePath_);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(this, "파일 저장 실패",
                              QString("파일을 저장할 수 없습니다.\n%1").arg(file.errorString()));
        return false;
    }

    QJsonArray array;
    for (const Book &book : books_)
        array.append(book.toJson());

    const qint64 written = file.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
    if (written < 0) {
        QMessageBox::critical(this, "파일 저장 실패",
                              QString("파일을 기록하지 못했습니다.\n%1").arg(file.errorString()));
        return false;
    }

    if (showMessage) {
        QMessageBox::information(
            this, "저장 완료",
            QString("도서 정보 %1권을 저장했습니다.\n%2")
                .arg(books_.size())
                .arg(QDir::toNativeSeparators(dataFilePath_)));
    }
    return true;
}

int MainWindow::selectedBookIndex() const
{
    const int row = table_->currentRow();
    if (row < 0 || !table_->item(row, IdColumn))
        return -1;

    bool ok = false;
    const int index = table_->item(row, IdColumn)->data(BookIndexRole).toInt(&ok);
    return ok && index >= 0 && index < books_.size() ? index : -1;
}

bool MainWindow::idExists(const QString &id) const
{
    for (const Book &book : books_) {
        if (book.id.compare(id, Qt::CaseInsensitive) == 0)
            return true;
    }
    return false;
}

void MainWindow::showStatus(const QString &message)
{
    statusBar()->showMessage(message, 7000);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (saveToFile())
        event->accept();
    else
        event->ignore();
}
