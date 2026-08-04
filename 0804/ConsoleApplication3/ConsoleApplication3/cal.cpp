#include <windows.h>
#include <string>

HWND hEdit1, hEdit2, hResult;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        CreateWindow("STATIC", "숫자1:", WS_VISIBLE | WS_CHILD,20, 20, 50, 20, hwnd, NULL, NULL, NULL);

        hEdit1 = CreateWindow("EDIT", "",WS_VISIBLE | WS_CHILD | WS_BORDER,80, 20, 100, 20, hwnd, NULL, NULL, NULL);

        CreateWindow("STATIC", "숫자2:", WS_VISIBLE | WS_CHILD,20, 60, 50, 20, hwnd, NULL, NULL, NULL);

        hEdit2 = CreateWindow("EDIT", "",WS_VISIBLE | WS_CHILD | WS_BORDER,80, 60, 100, 20, hwnd, NULL, NULL, NULL);

        CreateWindow("BUTTON", "+",WS_VISIBLE | WS_CHILD,20, 100, 40, 30, hwnd, (HMENU)1, NULL, NULL);

        CreateWindow("BUTTON", "-",WS_VISIBLE | WS_CHILD,70, 100, 40, 30, hwnd, (HMENU)2, NULL, NULL);

        CreateWindow("BUTTON", "*",WS_VISIBLE | WS_CHILD,120, 100, 40, 30, hwnd, (HMENU)3, NULL, NULL);

        CreateWindow("BUTTON", "/",WS_VISIBLE | WS_CHILD,170, 100, 40, 30, hwnd, (HMENU)4, NULL, NULL);

        hResult = CreateWindow("STATIC", "결과:",WS_VISIBLE | WS_CHILD,20, 150, 250, 30, hwnd, NULL, NULL, NULL);

        break;

    case WM_COMMAND:
    {
        char buf1[100], buf2[100], result[100];

        GetWindowText(hEdit1, buf1, 100);
        GetWindowText(hEdit2, buf2, 100);

        double a = atof(buf1);
        double b = atof(buf2);
        double c = 0;

        switch (LOWORD(wParam))
        {
        case 1:
            c = a + b;
            break;
        case 2:
            c = a - b;
            break;
        case 3:
            c = a * b;
            break;
        case 4:
            if (b == 0)
            {
                SetWindowText(hResult, "결과: 0으로 나눌 수 없습니다.");
                return 0;
            }
            c = a / b;
            break;
        }

        sprintf_s(result, "결과: %.2f", c);
        SetWindowText(hResult, result);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Calculator";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        "Calculator",
        "C++ 계산기",
        WS_OVERLAPPEDWINDOW,
        300, 200, 300, 250,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}