#include <windows.h>
#include <string>
#include <sstream>

HWND hDisplay;

double first = 0;
char op = 0;
bool newNumber = true;


void AddText(const char* text)
{
    char buf[256];
    GetWindowTextA(hDisplay, buf, 256);

    std::string value = buf;

    if (newNumber)
        value = "";

    value += text;

    SetWindowTextA(hDisplay, value.c_str());
    newNumber = false;
}


double GetDisplay()
{
    char buf[256];
    GetWindowTextA(hDisplay, buf, 256);

    return atof(buf);
}


void Calculate()
{
    double second = GetDisplay();
    double result = 0;

    switch (op)
    {
    case '+':
        result = first + second;
        break;

    case '-':
        result = first - second;
        break;

    case '*':
        result = first * second;
        break;

    case '/':
        if (second != 0)
            result = first / second;
        break;
    }

    std::ostringstream ss;
    ss << result;

    SetWindowTextA(hDisplay, ss.str().c_str());

    newNumber = true;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam)
{

    switch (msg)
    {

    case WM_CREATE:
    {
        hDisplay = CreateWindowA(
            "EDIT",
            "0",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT,
            20, 20, 230, 40,
            hwnd, NULL, NULL, NULL);


        const char* btn[] =
        {
            "7","8","9","/",
            "4","5","6","*",
            "1","2","3","-",
            "0","C","=","+"
        };


        int x, y;
        int id = 1;


        for (int i = 0;i < 16;i++)
        {
            x = 20 + (i % 4) * 60;
            y = 80 + (i / 4) * 50;


            CreateWindowA(
                "BUTTON",btn[i],WS_VISIBLE | WS_CHILD,x, y, 50, 40,hwnd,(HMENU)(INT_PTR)id++,
                NULL,
                NULL);
        }

    }
    break;


    case WM_COMMAND:
    {
        int id = LOWORD(wParam);


        if (id >= 1 && id <= 16)
        {

            switch (id)
            {

                // 숫자
            case 1:AddText("7");break;
            case 2:AddText("8");break;
            case 3:AddText("9");break;

            case 5:AddText("4");break;
            case 6:AddText("5");break;
            case 7:AddText("6");break;

            case 9:AddText("1");break;
            case 10:AddText("2");break;
            case 11:AddText("3");break;

            case 13:AddText("0");break;


                // 연산자
            case 4:
                first = GetDisplay();
                op = '/';
                newNumber = true;
                break;

            case 8:
                first = GetDisplay();
                op = '*';
                newNumber = true;
                break;


            case 12:
                first = GetDisplay();
                op = '-';
                newNumber = true;
                break;


            case 16:
                first = GetDisplay();
                op = '+';
                newNumber = true;
                break;



                // C
            case 14:
                SetWindowTextA(hDisplay, "0");
                first = 0;
                op = 0;
                break;


                // =
            case 15:
                Calculate();
                break;

            }

        }

    }
    break;



    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}



int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOW;


    WNDCLASSA wc = {};

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Calculator";


    RegisterClassA(&wc);



    HWND hwnd = CreateWindowA(
        "Calculator",
        "C++ 계산기",
        WS_OVERLAPPEDWINDOW,
        500, 200,
        290, 350,
        NULL, NULL,
        hInstance,
        NULL);



    ShowWindow(hwnd, nCmdShow);



    MSG msg{};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    return 0;
}