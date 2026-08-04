#pragma once

#include "book.h"

#include <QMainWindow>
#include <QVector>

class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

class MainWindow final : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void buildUi();
    void connectSignals();
    void addBook();
    void searchBooks();
    void loanBook();
    void returnBook();
    void deleteBook();
    void clearInputs();
    void refreshTable();
    void loadFromFile();
    bool saveToFile(bool showMessage = false);
    int selectedBookIndex() const;
    bool idExists(const QString &id) const;
    void showStatus(const QString &message);

    QVector<Book> books_;
    QString dataFilePath_;

    QLineEdit *idEdit_ = nullptr;
    QLineEdit *titleEdit_ = nullptr;
    QLineEdit *authorEdit_ = nullptr;
    QLineEdit *publisherEdit_ = nullptr;
    QLineEdit *searchEdit_ = nullptr;
    QLabel *countLabel_ = nullptr;
    QPushButton *addButton_ = nullptr;
    QPushButton *clearButton_ = nullptr;
    QPushButton *loanButton_ = nullptr;
    QPushButton *returnButton_ = nullptr;
    QPushButton *deleteButton_ = nullptr;
    QPushButton *saveButton_ = nullptr;
    QTableWidget *table_ = nullptr;
};
