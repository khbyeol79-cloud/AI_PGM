#include <windows.h>
#include <string>
#include <sstream>

HWND display;

double result = 0;
char operation = 0;
bool newInput = true;


double GetNumber()
{
    char buf[100];
    GetWindowTextA(display, buf, 100);
    return atof(buf);
}


void SetNumber(double value)
{
    std::ostringstream ss;
    ss << value;

    SetWindowTextA(display, ss.str().c_str());
}


void Calculate(double next)
{
    switch (operation)
    {
    case '+':
        result += next;
        break;

    case '-':
        result -= next;
        break;

    case '*':
        result *= next;
        break;

    case '/':
        if (next != 0)
            result /= next;
        break;
    }

    SetNumber(result);
}



void InputNumber(const char* num)
{
    char buf[100];

    GetWindowTextA(display, buf, 100);

    std::string text = buf;


    if (newInput || text == "0")
        text = "";


    text += num;


    SetWindowTextA(display, text.c_str());

    newInput = false;
}



void InputOperator(char op)
{
    double current = GetNumber();


    if (operation != 0 && !newInput)
    {
        Calculate(current);
    }
    else
    {
        result = current;
    }


    operation = op;

    newInput = true;
}



LRESULT CALLBACK WndProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{

    switch (msg)
    {


    case WM_CREATE:
    {

        display = CreateWindowA(
            "EDIT",
            "0",
            WS_CHILD | WS_VISIBLE |
            WS_BORDER |
            ES_RIGHT,

            20, 20,
            240, 40,

            hwnd,
            NULL,
            NULL,
            NULL);



        const char* button[20] =
        {
        "7","8","9","/",
        "4","5","6","*",
        "1","2","3","-",
        "0","C","=","+"
        };


        int id = 1;


        for (int i = 0;i < 16;i++)
        {

            int x = 20 + (i % 4) * 60;
            int y = 80 + (i / 4) * 50;


            CreateWindowA(
                "BUTTON",
                button[i],
                WS_CHILD | WS_VISIBLE,

                x, y,
                50, 40,

                hwnd,
                (HMENU)(INT_PTR)id,
                NULL,
                NULL);


            id++;

        }

    }
    break;



    case WM_COMMAND:
    {

        int id = LOWORD(wParam);


        switch (id)
        {


        case 1: InputNumber("7");break;
        case 2: InputNumber("8");break;
        case 3: InputNumber("9");break;


        case 5: InputNumber("4");break;
        case 6: InputNumber("5");break;
        case 7: InputNumber("6");break;


        case 9: InputNumber("1");break;
        case 10:InputNumber("2");break;
        case 11:InputNumber("3");break;


        case 13:InputNumber("0");break;



        case 4:
            InputOperator('/');
            break;


        case 8:
            InputOperator('*');
            break;


        case 12:
            InputOperator('-');
            break;


        case 16:
            InputOperator('+');
            break;



        case 15:   // =
        {
            double value = GetNumber();

            if (!newInput)
                Calculate(value);

            operation = 0;
            newInput = true;

        }
        break;



        case 14:   // C
        {
            SetWindowTextA(display, "0");

            result = 0;
            operation = 0;
            newInput = true;

        }
        break;



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

    WNDCLASSA wc = {};

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Calculator";


    RegisterClassA(&wc);



    HWND hwnd = CreateWindowA(

        "Calculator",
        "Windows Style Calculator",

        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,

        500, 200,
        300, 350,

        NULL,
        NULL,
        hInstance,
        NULL);


    ShowWindow(hwnd, SW_SHOW);



    MSG msg = {};


    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    return 0;
}