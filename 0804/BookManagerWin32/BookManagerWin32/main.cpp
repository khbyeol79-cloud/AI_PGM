#define NOMINMAX

#include <windows.h>
#include <commctrl.h>
#include <shlobj.h>

#include <algorithm>
#include <cstdint>
#include <cwchar>
#include <cwctype>
#include <filesystem>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Shell32.lib")

struct Book
{
    std::wstring id;
    std::wstring title;
    std::wstring author;
    std::wstring publisher;
    bool borrowed = false;
    std::wstring borrower;
    std::wstring borrowedDate;
};

namespace
{
constexpr wchar_t WindowClassName[] = L"BookManagerWin32Window";

enum ControlId
{
    IdEdit = 101,
    TitleEdit,
    AuthorEdit,
    PublisherEdit,
    SearchEdit,
    BorrowerEdit,
    AddButton,
    ClearButton,
    LoanButton,
    ReturnButton,
    DeleteButton,
    SaveButton,
    BookList,
    CountLabel,
    PathLabel
};

HINSTANCE g_instance = nullptr;
HWND g_mainWindow = nullptr;
HWND g_idEdit = nullptr;
HWND g_titleEdit = nullptr;
HWND g_authorEdit = nullptr;
HWND g_publisherEdit = nullptr;
HWND g_searchEdit = nullptr;
HWND g_borrowerEdit = nullptr;
HWND g_addButton = nullptr;
HWND g_clearButton = nullptr;
HWND g_loanButton = nullptr;
HWND g_returnButton = nullptr;
HWND g_deleteButton = nullptr;
HWND g_saveButton = nullptr;
HWND g_bookList = nullptr;
HWND g_countLabel = nullptr;
HWND g_pathLabel = nullptr;
HWND g_labels[6]{};
HFONT g_font = nullptr;
std::vector<Book> g_books;
std::wstring g_dataFilePath;

std::wstring GetText(HWND control)
{
    const int length = GetWindowTextLengthW(control);
    std::wstring text(static_cast<size_t>(length) + 1, L'\0');
    if (length > 0) {
        GetWindowTextW(control, text.data(), length + 1);
        text.resize(static_cast<size_t>(length));
    } else {
        text.clear();
    }
    return text;
}

void SetFont(HWND control)
{
    SendMessageW(control, WM_SETFONT, reinterpret_cast<WPARAM>(g_font), TRUE);
}

HWND MakeControl(const wchar_t *className, const wchar_t *text, DWORD style,
                 int id, DWORD extendedStyle = 0)
{
    HWND control = CreateWindowExW(
        extendedStyle, className, text, WS_CHILD | WS_VISIBLE | style,
        0, 0, 100, 25, g_mainWindow,
        reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), g_instance, nullptr);
    SetFont(control);
    return control;
}

HWND MakeLabel(const wchar_t *text, int id = 0)
{
    return MakeControl(L"STATIC", text, SS_LEFT | SS_CENTERIMAGE, id);
}

std::string ToUtf8(const std::wstring &text)
{
    if (text.empty())
        return {};
    const int size = WideCharToMultiByte(CP_UTF8, 0, text.data(),
                                         static_cast<int>(text.size()),
                                         nullptr, 0, nullptr, nullptr);
    std::string result(static_cast<size_t>(size), '\0');
    WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
                        result.data(), size, nullptr, nullptr);
    return result;
}

std::wstring FromUtf8(const std::string &text)
{
    if (text.empty())
        return {};
    const int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
                                         text.data(), static_cast<int>(text.size()),
                                         nullptr, 0);
    if (size <= 0)
        return {};
    std::wstring result(static_cast<size_t>(size), L'\0');
    MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(),
                        static_cast<int>(text.size()), result.data(), size);
    return result;
}

bool WriteString(std::ofstream &file, const std::wstring &value)
{
    const std::string utf8 = ToUtf8(value);
    const auto size = static_cast<std::uint32_t>(utf8.size());
    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    file.write(utf8.data(), static_cast<std::streamsize>(utf8.size()));
    return file.good();
}

bool ReadString(std::ifstream &file, std::wstring &value)
{
    std::uint32_t size = 0;
    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    if (!file.good() || size > 10 * 1024 * 1024)
        return false;
    std::string utf8(size, '\0');
    file.read(utf8.data(), static_cast<std::streamsize>(size));
    if (!file.good())
        return false;
    value = FromUtf8(utf8);
    return true;
}

std::wstring BuildDataPath()
{
    wchar_t appData[MAX_PATH]{};
    if (FAILED(SHGetFolderPathW(nullptr, CSIDL_APPDATA | CSIDL_FLAG_CREATE,
                                nullptr, SHGFP_TYPE_CURRENT, appData))) {
        GetModuleFileNameW(nullptr, appData, MAX_PATH);
        std::wstring fallback = appData;
        const size_t separator = fallback.find_last_of(L"\\/");
        return fallback.substr(0, separator + 1) + L"books.dat";
    }

    std::wstring directory = std::wstring(appData) + L"\\BookManagerWin32";
    CreateDirectoryW(directory.c_str(), nullptr);
    return directory + L"\\books.dat";
}

bool SaveBooks(bool showMessage)
{
    std::ofstream file(std::filesystem::path(g_dataFilePath),
                       std::ios::binary | std::ios::trunc);
    if (!file) {
        MessageBoxW(g_mainWindow, L"도서 파일을 저장할 수 없습니다.",
                    L"파일 저장 실패", MB_OK | MB_ICONERROR);
        return false;
    }

    constexpr char signature[4] = {'B', 'K', 'M', '1'};
    file.write(signature, sizeof(signature));
    const auto count = static_cast<std::uint32_t>(g_books.size());
    file.write(reinterpret_cast<const char *>(&count), sizeof(count));

    for (const Book &book : g_books) {
        const std::uint8_t borrowed = book.borrowed ? 1 : 0;
        if (!WriteString(file, book.id) || !WriteString(file, book.title)
            || !WriteString(file, book.author) || !WriteString(file, book.publisher)) {
            break;
        }
        file.write(reinterpret_cast<const char *>(&borrowed), sizeof(borrowed));
        if (!WriteString(file, book.borrower) || !WriteString(file, book.borrowedDate))
            break;
    }

    if (!file.good()) {
        MessageBoxW(g_mainWindow, L"파일을 기록하는 중 오류가 발생했습니다.",
                    L"파일 저장 실패", MB_OK | MB_ICONERROR);
        return false;
    }

    if (showMessage) {
        std::wstring message = L"도서 정보 " + std::to_wstring(g_books.size())
            + L"권을 저장했습니다.\n\n" + g_dataFilePath;
        MessageBoxW(g_mainWindow, message.c_str(), L"저장 완료",
                    MB_OK | MB_ICONINFORMATION);
    }
    return true;
}

void LoadBooks()
{
    std::ifstream file(std::filesystem::path(g_dataFilePath), std::ios::binary);
    if (!file)
        return;

    char signature[4]{};
    std::uint32_t count = 0;
    file.read(signature, sizeof(signature));
    file.read(reinterpret_cast<char *>(&count), sizeof(count));
    if (!file.good() || std::string(signature, 4) != "BKM1" || count > 100000) {
        MessageBoxW(g_mainWindow, L"저장 파일의 형식이 올바르지 않습니다.",
                    L"파일 불러오기 실패", MB_OK | MB_ICONWARNING);
        return;
    }

    std::vector<Book> loaded;
    loaded.reserve(count);
    for (std::uint32_t i = 0; i < count; ++i) {
        Book book;
        std::uint8_t borrowed = 0;
        if (!ReadString(file, book.id) || !ReadString(file, book.title)
            || !ReadString(file, book.author) || !ReadString(file, book.publisher)) {
            loaded.clear();
            break;
        }
        file.read(reinterpret_cast<char *>(&borrowed), sizeof(borrowed));
        if (!file.good() || !ReadString(file, book.borrower)
            || !ReadString(file, book.borrowedDate)) {
            loaded.clear();
            break;
        }
        book.borrowed = borrowed != 0;
        loaded.push_back(std::move(book));
    }

    if (loaded.size() == count) {
        g_books = std::move(loaded);
    } else {
        MessageBoxW(g_mainWindow, L"저장 파일을 끝까지 읽지 못했습니다.",
                    L"파일 불러오기 실패", MB_OK | MB_ICONWARNING);
    }
}

std::wstring Lower(std::wstring value)
{
    std::transform(value.begin(), value.end(), value.begin(),
                   [](wchar_t ch) { return static_cast<wchar_t>(towlower(ch)); });
    return value;
}

bool Contains(const std::wstring &value, const std::wstring &keyword)
{
    return Lower(value).find(keyword) != std::wstring::npos;
}

void RefreshList()
{
    const std::wstring keyword = Lower(GetText(g_searchEdit));
    ListView_DeleteAllItems(g_bookList);

    int visible = 0;
    for (size_t index = 0; index < g_books.size(); ++index) {
        const Book &book = g_books[index];
        if (!keyword.empty() && !Contains(book.id, keyword) && !Contains(book.title, keyword)
            && !Contains(book.author, keyword) && !Contains(book.publisher, keyword)) {
            continue;
        }

        LVITEMW item{};
        item.mask = LVIF_TEXT | LVIF_PARAM;
        item.iItem = visible;
        item.pszText = const_cast<wchar_t *>(book.id.c_str());
        item.lParam = static_cast<LPARAM>(index);
        const int row = ListView_InsertItem(g_bookList, &item);

        ListView_SetItemText(g_bookList, row, 1, const_cast<wchar_t *>(book.title.c_str()));
        ListView_SetItemText(g_bookList, row, 2, const_cast<wchar_t *>(book.author.c_str()));
        ListView_SetItemText(g_bookList, row, 3, const_cast<wchar_t *>(book.publisher.c_str()));
        ListView_SetItemText(g_bookList, row, 4,
            const_cast<wchar_t *>(book.borrowed ? L"대출 중" : L"대출 가능"));
        ListView_SetItemText(g_bookList, row, 5, const_cast<wchar_t *>(book.borrower.c_str()));
        ListView_SetItemText(g_bookList, row, 6, const_cast<wchar_t *>(book.borrowedDate.c_str()));
        ++visible;
    }

    std::wstring countText = L"검색 결과 " + std::to_wstring(visible)
        + L"권 / 전체 " + std::to_wstring(g_books.size()) + L"권";
    SetWindowTextW(g_countLabel, countText.c_str());
}

int SelectedBookIndex()
{
    const int row = ListView_GetNextItem(g_bookList, -1, LVNI_SELECTED);
    if (row < 0)
        return -1;
    LVITEMW item{};
    item.mask = LVIF_PARAM;
    item.iItem = row;
    if (!ListView_GetItem(g_bookList, &item))
        return -1;
    const auto index = static_cast<size_t>(item.lParam);
    return index < g_books.size() ? static_cast<int>(index) : -1;
}

void ClearInputs()
{
    for (HWND edit : {g_idEdit, g_titleEdit, g_authorEdit, g_publisherEdit})
        SetWindowTextW(edit, L"");
    SetFocus(g_idEdit);
}

void AddBook()
{
    Book book;
    book.id = GetText(g_idEdit);
    book.title = GetText(g_titleEdit);
    book.author = GetText(g_authorEdit);
    book.publisher = GetText(g_publisherEdit);

    if (book.id.empty() || book.title.empty() || book.author.empty()) {
        MessageBoxW(g_mainWindow, L"도서번호, 도서명, 저자는 필수 입력 항목입니다.",
                    L"입력 확인", MB_OK | MB_ICONWARNING);
        return;
    }

    for (const Book &existing : g_books) {
        if (_wcsicmp(existing.id.c_str(), book.id.c_str()) == 0) {
            MessageBoxW(g_mainWindow, L"이미 등록된 도서번호입니다.",
                        L"중복 도서번호", MB_OK | MB_ICONWARNING);
            SetFocus(g_idEdit);
            return;
        }
    }

    g_books.push_back(std::move(book));
    SaveBooks(false);
    ClearInputs();
    RefreshList();
}

std::wstring Today()
{
    SYSTEMTIME time{};
    GetLocalTime(&time);
    wchar_t buffer[16]{};
    swprintf_s(buffer, L"%04u-%02u-%02u", time.wYear, time.wMonth, time.wDay);
    return buffer;
}

void LoanBook()
{
    const int index = SelectedBookIndex();
    if (index < 0) {
        MessageBoxW(g_mainWindow, L"대출할 도서를 목록에서 선택하세요.",
                    L"도서 선택", MB_OK | MB_ICONINFORMATION);
        return;
    }
    Book &book = g_books[static_cast<size_t>(index)];
    if (book.borrowed) {
        MessageBoxW(g_mainWindow, L"이미 대출 중인 도서입니다.",
                    L"대출 불가", MB_OK | MB_ICONWARNING);
        return;
    }

    const std::wstring borrower = GetText(g_borrowerEdit);
    if (borrower.empty()) {
        MessageBoxW(g_mainWindow, L"위쪽 대출자 입력란에 이름을 입력하세요.",
                    L"대출자 입력", MB_OK | MB_ICONWARNING);
        SetFocus(g_borrowerEdit);
        return;
    }

    book.borrowed = true;
    book.borrower = borrower;
    book.borrowedDate = Today();
    SetWindowTextW(g_borrowerEdit, L"");
    SaveBooks(false);
    RefreshList();
}

void ReturnBook()
{
    const int index = SelectedBookIndex();
    if (index < 0) {
        MessageBoxW(g_mainWindow, L"반납할 도서를 목록에서 선택하세요.",
                    L"도서 선택", MB_OK | MB_ICONINFORMATION);
        return;
    }
    Book &book = g_books[static_cast<size_t>(index)];
    if (!book.borrowed) {
        MessageBoxW(g_mainWindow, L"현재 대출 중인 도서가 아닙니다.",
                    L"반납 확인", MB_OK | MB_ICONINFORMATION);
        return;
    }
    book.borrowed = false;
    book.borrower.clear();
    book.borrowedDate.clear();
    SaveBooks(false);
    RefreshList();
}

void DeleteBook()
{
    const int index = SelectedBookIndex();
    if (index < 0) {
        MessageBoxW(g_mainWindow, L"삭제할 도서를 목록에서 선택하세요.",
                    L"도서 선택", MB_OK | MB_ICONINFORMATION);
        return;
    }
    const Book &book = g_books[static_cast<size_t>(index)];
    if (book.borrowed) {
        MessageBoxW(g_mainWindow, L"대출 중인 도서는 반납 후 삭제할 수 있습니다.",
                    L"삭제 불가", MB_OK | MB_ICONWARNING);
        return;
    }
    std::wstring message = L"'" + book.title + L"' 도서를 정말 삭제하시겠습니까?";
    if (MessageBoxW(g_mainWindow, message.c_str(), L"도서 삭제",
                    MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES) {
        return;
    }
    g_books.erase(g_books.begin() + index);
    SaveBooks(false);
    RefreshList();
}

void CreateColumns()
{
    const wchar_t *titles[] = {L"도서번호", L"도서명", L"저자", L"출판사",
                               L"상태", L"대출자", L"대출일"};
    const int widths[] = {100, 230, 130, 130, 85, 110, 100};
    for (int i = 0; i < 7; ++i) {
        LVCOLUMNW column{};
        column.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
        column.pszText = const_cast<wchar_t *>(titles[i]);
        column.cx = widths[i];
        column.iSubItem = i;
        ListView_InsertColumn(g_bookList, i, &column);
    }
}

void BuildInterface()
{
    g_font = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));

    g_labels[0] = MakeLabel(L"도서번호 *");
    g_idEdit = MakeControl(L"EDIT", L"", WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP, IdEdit,
                           WS_EX_CLIENTEDGE);
    g_labels[1] = MakeLabel(L"도서명 *");
    g_titleEdit = MakeControl(L"EDIT", L"", WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP, TitleEdit,
                              WS_EX_CLIENTEDGE);
    g_labels[2] = MakeLabel(L"저자 *");
    g_authorEdit = MakeControl(L"EDIT", L"", WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP, AuthorEdit,
                               WS_EX_CLIENTEDGE);
    g_labels[3] = MakeLabel(L"출판사");
    g_publisherEdit = MakeControl(L"EDIT", L"", WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP,
                                  PublisherEdit, WS_EX_CLIENTEDGE);

    g_addButton = MakeControl(L"BUTTON", L"도서 등록", BS_PUSHBUTTON | WS_TABSTOP, AddButton);
    g_clearButton = MakeControl(L"BUTTON", L"입력 지우기", BS_PUSHBUTTON | WS_TABSTOP, ClearButton);

    g_labels[4] = MakeLabel(L"도서 검색");
    g_searchEdit = MakeControl(L"EDIT", L"", WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP, SearchEdit,
                               WS_EX_CLIENTEDGE);
    g_labels[5] = MakeLabel(L"대출자");
    g_borrowerEdit = MakeControl(L"EDIT", L"", WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP,
                                 BorrowerEdit, WS_EX_CLIENTEDGE);
    g_countLabel = MakeControl(L"STATIC", L"", SS_RIGHT | SS_CENTERIMAGE, CountLabel);

    g_bookList = MakeControl(WC_LISTVIEWW, L"",
        LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS | WS_BORDER | WS_TABSTOP,
        BookList, WS_EX_CLIENTEDGE);
    ListView_SetExtendedListViewStyle(g_bookList,
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);
    CreateColumns();

    g_loanButton = MakeControl(L"BUTTON", L"선택 도서 대출", BS_PUSHBUTTON | WS_TABSTOP, LoanButton);
    g_returnButton = MakeControl(L"BUTTON", L"선택 도서 반납", BS_PUSHBUTTON | WS_TABSTOP, ReturnButton);
    g_deleteButton = MakeControl(L"BUTTON", L"선택 도서 삭제", BS_PUSHBUTTON | WS_TABSTOP, DeleteButton);
    g_saveButton = MakeControl(L"BUTTON", L"파일 저장", BS_PUSHBUTTON | WS_TABSTOP, SaveButton);
    g_pathLabel = MakeControl(L"STATIC", L"", SS_LEFT | SS_CENTERIMAGE, PathLabel);
    SetWindowTextW(g_pathLabel, (L"저장 파일: " + g_dataFilePath).c_str());
}

void Move(HWND control, int x, int y, int width, int height)
{
    MoveWindow(control, x, y, std::max(1, width), std::max(1, height), TRUE);
}

void LayoutControls(int clientWidth, int clientHeight)
{
    const int margin = 14;
    const int labelWidth = 75;
    const int editHeight = 26;
    const int gap = 8;
    const int topWidth = std::max(720, clientWidth - margin * 2 - 190);
    const int fieldWidth = (topWidth - labelWidth * 2 - gap * 3) / 2;

    Move(g_labels[0], margin, 14, labelWidth, editHeight);
    Move(g_idEdit, margin + labelWidth, 14, fieldWidth, editHeight);
    Move(g_labels[1], margin + labelWidth + fieldWidth + gap, 14, labelWidth, editHeight);
    Move(g_titleEdit, margin + labelWidth * 2 + fieldWidth + gap, 14, fieldWidth, editHeight);

    Move(g_labels[2], margin, 48, labelWidth, editHeight);
    Move(g_authorEdit, margin + labelWidth, 48, fieldWidth, editHeight);
    Move(g_labels[3], margin + labelWidth + fieldWidth + gap, 48, labelWidth, editHeight);
    Move(g_publisherEdit, margin + labelWidth * 2 + fieldWidth + gap, 48, fieldWidth, editHeight);

    Move(g_addButton, clientWidth - margin - 180, 14, 86, 60);
    Move(g_clearButton, clientWidth - margin - 88, 14, 88, 60);

    Move(g_labels[4], margin, 89, labelWidth, editHeight);
    Move(g_searchEdit, margin + labelWidth, 89, std::max(180, clientWidth / 3), editHeight);
    const int borrowerLabelX = margin + labelWidth + std::max(180, clientWidth / 3) + gap;
    Move(g_labels[5], borrowerLabelX, 89, 58, editHeight);
    Move(g_borrowerEdit, borrowerLabelX + 58, 89, 150, editHeight);
    Move(g_countLabel, clientWidth - margin - 190, 89, 190, editHeight);

    const int listTop = 126;
    const int bottomArea = 92;
    Move(g_bookList, margin, listTop, clientWidth - margin * 2,
         clientHeight - listTop - bottomArea);

    const int buttonY = clientHeight - 78;
    Move(g_loanButton, margin, buttonY, 130, 34);
    Move(g_returnButton, margin + 138, buttonY, 130, 34);
    Move(g_deleteButton, margin + 276, buttonY, 130, 34);
    Move(g_saveButton, clientWidth - margin - 105, buttonY, 105, 34);
    Move(g_pathLabel, margin, clientHeight - 35, clientWidth - margin * 2, 22);
}

LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CREATE:
        g_mainWindow = window;
        g_dataFilePath = BuildDataPath();
        BuildInterface();
        LoadBooks();
        RefreshList();
        return 0;

    case WM_SIZE:
        LayoutControls(LOWORD(lParam), HIWORD(lParam));
        return 0;

    case WM_GETMINMAXINFO:
        reinterpret_cast<MINMAXINFO *>(lParam)->ptMinTrackSize = {850, 540};
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == SearchEdit && HIWORD(wParam) == EN_CHANGE) {
            RefreshList();
            return 0;
        }
        if (HIWORD(wParam) == BN_CLICKED) {
            switch (LOWORD(wParam)) {
            case AddButton: AddBook(); return 0;
            case ClearButton: ClearInputs(); return 0;
            case LoanButton: LoanBook(); return 0;
            case ReturnButton: ReturnBook(); return 0;
            case DeleteButton: DeleteBook(); return 0;
            case SaveButton: SaveBooks(true); return 0;
            default: break;
            }
        }
        break;

    case WM_CLOSE:
        if (SaveBooks(false))
            DestroyWindow(window);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int showCommand)
{
    g_instance = instance;

    INITCOMMONCONTROLSEX controls{sizeof(INITCOMMONCONTROLSEX), ICC_LISTVIEW_CLASSES};
    InitCommonControlsEx(&controls);

    WNDCLASSEXW windowClass{};
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProcedure;
    windowClass.hInstance = instance;
    windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    windowClass.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    windowClass.lpszClassName = WindowClassName;
    windowClass.hIconSm = LoadIconW(nullptr, IDI_APPLICATION);

    if (!RegisterClassExW(&windowClass))
        return 1;

    HWND window = CreateWindowExW(
        0, WindowClassName, L"도서관리 프로그램",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, 1100, 680,
        nullptr, nullptr, instance, nullptr);
    if (!window)
        return 1;

    ShowWindow(window, showCommand);
    UpdateWindow(window);

    MSG message{};
    while (GetMessageW(&message, nullptr, 0, 0) > 0) {
        if (!IsDialogMessageW(window, &message)) {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }
    return static_cast<int>(message.wParam);
}
