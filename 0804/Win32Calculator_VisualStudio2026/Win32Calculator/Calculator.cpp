#define UNICODE
#define _UNICODE
#include <windows.h>
#include <cmath>
#include <cwchar>
#include <string>

namespace {
constexpr wchar_t kClassName[] = L"NativeWin32Calculator";
constexpr int ID_DISPLAY = 100;
constexpr int ID_FIRST_BUTTON = 200;
constexpr int COLS = 4;
constexpr int ROWS = 6;

HWND g_display = nullptr;
HFONT g_displayFont = nullptr;
HFONT g_buttonFont = nullptr;
double g_accumulator = 0.0;
double g_lastOperand = 0.0;
wchar_t g_pendingOp = 0;
wchar_t g_lastOp = 0;
bool g_newEntry = true;
bool g_error = false;

struct ButtonDef { const wchar_t* text; wchar_t key; };

const ButtonDef kButtons[ROWS][COLS] = {
    {{L"%", L'%'}, {L"CE", L'E'}, {L"C", L'C'}, {L"⌫", L'B'}},
    {{L"1/x", L'R'}, {L"x²", L'S'}, {L"√x", L'Q'}, {L"÷", L'/'}},
    {{L"7", L'7'}, {L"8", L'8'}, {L"9", L'9'}, {L"×", L'*'}},
    {{L"4", L'4'}, {L"5", L'5'}, {L"6", L'6'}, {L"−", L'-'}},
    {{L"1", L'1'}, {L"2", L'2'}, {L"3", L'3'}, {L"+", L'+'}},
    {{L"±", L'N'}, {L"0", L'0'}, {L".", L'.'}, {L"=", L'='}}
};

std::wstring GetDisplayText() {
    int length = GetWindowTextLengthW(g_display);
    std::wstring text(static_cast<size_t>(length) + 1, L'\0');
    GetWindowTextW(g_display, text.data(), length + 1);
    text.resize(static_cast<size_t>(length));
    return text;
}

void SetDisplayText(const std::wstring& text) {
    SetWindowTextW(g_display, text.c_str());
}

double DisplayValue() {
    return std::wcstod(GetDisplayText().c_str(), nullptr);
}

std::wstring FormatNumber(double value) {
    if (std::abs(value) < 1e-15) value = 0.0;
    wchar_t buffer[64]{};
    swprintf_s(buffer, _countof(buffer), L"%.15g", value);
    return buffer;
}

void ShowError() {
    SetDisplayText(L"계산할 수 없습니다");
    g_error = true;
    g_newEntry = true;
    g_pendingOp = 0;
}

bool Apply(double left, wchar_t op, double right, double& result) {
    switch (op) {
    case L'+': result = left + right; break;
    case L'-': result = left - right; break;
    case L'*': result = left * right; break;
    case L'/':
        if (right == 0.0) return false;
        result = left / right;
        break;
    default: result = right; break;
    }
    return std::isfinite(result);
}

void ClearAll() {
    g_accumulator = 0.0;
    g_lastOperand = 0.0;
    g_pendingOp = 0;
    g_lastOp = 0;
    g_newEntry = true;
    g_error = false;
    SetDisplayText(L"0");
}

void EnterDigit(wchar_t digit) {
    if (g_error) ClearAll();
    std::wstring text = GetDisplayText();
    if (g_newEntry || text == L"0") {
        text.assign(1, digit);
        g_newEntry = false;
    } else if (text.size() < 16) {
        text.push_back(digit);
    }
    SetDisplayText(text);
}

void EnterDecimal() {
    if (g_error) ClearAll();
    std::wstring text = GetDisplayText();
    if (g_newEntry) {
        SetDisplayText(L"0.");
        g_newEntry = false;
    } else if (text.find(L'.') == std::wstring::npos && text.find(L'e') == std::wstring::npos) {
        text.push_back(L'.');
        SetDisplayText(text);
    }
}

void ChooseOperator(wchar_t op) {
    if (g_error) return;
    const double current = DisplayValue();
    if (g_pendingOp && !g_newEntry) {
        double result{};
        if (!Apply(g_accumulator, g_pendingOp, current, result)) {
            ShowError();
            return;
        }
        g_accumulator = result;
        SetDisplayText(FormatNumber(result));
    } else if (!g_pendingOp) {
        g_accumulator = current;
    }
    g_pendingOp = op;
    g_newEntry = true;
    g_lastOp = 0;
}

void Equals() {
    if (g_error) return;
    double operand = DisplayValue();
    wchar_t op = g_pendingOp;

    if (op) {
        if (g_newEntry) operand = g_accumulator;
        g_lastOp = op;
        g_lastOperand = operand;
    } else if (g_lastOp) {
        op = g_lastOp;
        operand = g_lastOperand;
        g_accumulator = DisplayValue();
    } else {
        return;
    }

    double result{};
    if (!Apply(g_accumulator, op, operand, result)) {
        ShowError();
        return;
    }
    SetDisplayText(FormatNumber(result));
    g_accumulator = result;
    g_pendingOp = 0;
    g_newEntry = true;
}

void UnaryOperation(wchar_t key) {
    if (g_error) return;
    double value = DisplayValue();
    switch (key) {
    case L'N': value = -value; break;
    case L'S': value *= value; break;
    case L'Q':
        if (value < 0.0) { ShowError(); return; }
        value = std::sqrt(value);
        break;
    case L'R':
        if (value == 0.0) { ShowError(); return; }
        value = 1.0 / value;
        break;
    case L'%':
        value = g_pendingOp ? g_accumulator * value / 100.0 : value / 100.0;
        break;
    }
    if (!std::isfinite(value)) { ShowError(); return; }
    SetDisplayText(FormatNumber(value));
    g_newEntry = false;
}

void ProcessKey(wchar_t key) {
    if (key >= L'0' && key <= L'9') { EnterDigit(key); return; }
    if (key == L'.') { EnterDecimal(); return; }
    if (key == L'+' || key == L'-' || key == L'*' || key == L'/') { ChooseOperator(key); return; }
    if (key == L'=') { Equals(); return; }
    if (key == L'C') { ClearAll(); return; }
    if (key == L'E') {
        if (g_error) ClearAll(); else { SetDisplayText(L"0"); g_newEntry = true; }
        return;
    }
    if (key == L'B') {
        if (g_error || g_newEntry) return;
        std::wstring text = GetDisplayText();
        if (text.size() <= 1 || (text.size() == 2 && text[0] == L'-')) text = L"0";
        else text.pop_back();
        SetDisplayText(text);
        return;
    }
    UnaryOperation(key);
}

void LayoutControls(HWND hwnd) {
    RECT rc{};
    GetClientRect(hwnd, &rc);
    const int margin = 12;
    const int gap = 7;
    const int displayHeight = 82;
    MoveWindow(g_display, margin, margin, rc.right - margin * 2, displayHeight, TRUE);
    const int top = margin + displayHeight + gap;
    const int buttonWidth = (rc.right - margin * 2 - gap * (COLS - 1)) / COLS;
    const int buttonHeight = (rc.bottom - top - margin - gap * (ROWS - 1)) / ROWS;
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            HWND button = GetDlgItem(hwnd, ID_FIRST_BUTTON + row * COLS + col);
            MoveWindow(button, margin + col * (buttonWidth + gap), top + row * (buttonHeight + gap),
                       buttonWidth, buttonHeight, TRUE);
        }
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        g_displayFont = CreateFontW(-34, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                   OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                   DEFAULT_PITCH, L"Segoe UI");
        g_buttonFont = CreateFontW(-21, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                  DEFAULT_PITCH, L"Segoe UI");
        g_display = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"0",
                                   WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY | ES_AUTOHSCROLL,
                                   0, 0, 0, 0, hwnd, reinterpret_cast<HMENU>(ID_DISPLAY),
                                   GetModuleHandleW(nullptr), nullptr);
        SendMessageW(g_display, WM_SETFONT, reinterpret_cast<WPARAM>(g_displayFont), TRUE);
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                const int id = ID_FIRST_BUTTON + row * COLS + col;
                HWND button = CreateWindowExW(0, L"BUTTON", kButtons[row][col].text,
                    WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                    0, 0, 0, 0, hwnd, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
                    GetModuleHandleW(nullptr), nullptr);
                SendMessageW(button, WM_SETFONT, reinterpret_cast<WPARAM>(g_buttonFont), TRUE);
            }
        }
        return 0;
    }
    case WM_SIZE:
        LayoutControls(hwnd);
        return 0;
    case WM_COMMAND: {
        const int id = LOWORD(wParam);
        if (id >= ID_FIRST_BUTTON && id < ID_FIRST_BUTTON + ROWS * COLS) {
            const int index = id - ID_FIRST_BUTTON;
            ProcessKey(kButtons[index / COLS][index % COLS].key);
            SetFocus(hwnd);
        }
        return 0;
    }
    case WM_KEYDOWN:
        if (wParam == VK_RETURN) ProcessKey(L'=');
        else if (wParam == VK_BACK) ProcessKey(L'B');
        else if (wParam == VK_ESCAPE) ProcessKey(L'C');
        else if (wParam == VK_DELETE) ProcessKey(L'E');
        else return DefWindowProcW(hwnd, msg, wParam, lParam);
        return 0;
    case WM_CHAR: {
        wchar_t key = static_cast<wchar_t>(wParam);
        if ((key >= L'0' && key <= L'9') || key == L'+' || key == L'-' ||
            key == L'*' || key == L'/' || key == L'%' || key == L'.' || key == L'=') {
            ProcessKey(key);
        }
        return 0;
    }
    case WM_GETMINMAXINFO: {
        auto* info = reinterpret_cast<MINMAXINFO*>(lParam);
        info->ptMinTrackSize = {360, 540};
        return 0;
    }
    case WM_DESTROY:
        DeleteObject(g_displayFont);
        DeleteObject(g_buttonFont);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}
} // namespace

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int showCommand) {
    SetProcessDPIAware();
    WNDCLASSEXW wc{sizeof(wc)};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszClassName = kClassName;
    wc.hIconSm = wc.hIcon;
    if (!RegisterClassExW(&wc)) return 1;

    HWND hwnd = CreateWindowExW(0, kClassName, L"계산기", WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT, 390, 650,
                                nullptr, nullptr, instance, nullptr);
    if (!hwnd) return 1;
    ShowWindow(hwnd, showCommand);
    UpdateWindow(hwnd);

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return static_cast<int>(msg.wParam);
}
