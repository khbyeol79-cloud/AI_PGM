# 0804 C/C++ GUI 프로그래밍 학습내용 정리

> 정리 기준: [`AI_PGM/0804`](https://github.com/khbyeol79-cloud/AI_PGM/tree/bb656901e31aabe57289765df40485507926964f/0804) 폴더의 소스 코드  
> 기준 커밋: `bb656901e31aabe57289765df40485507926964f`

## 1. 학습 내용 한눈에 보기

| 구분 | 관련 파일·프로젝트 | 핵심 학습 내용 |
|---|---|---|
| 함수 기초 | `ConsoleApplication3.cpp` | 매개변수, 반환값, `bool`, 함수 호출 |
| Win32 GUI 입문 | `cal.cpp` | 윈도우 생성, 입력창·버튼·레이블, 메시지 처리 |
| 버튼식 계산기 | `cal1.cpp` | 계산기 상태 변수, 버튼 ID, 숫자 입력과 단일 계산 |
| 연속 계산기 | `cal2.cpp` | 누적 결과, 연속 연산, 입력 상태 전환 |
| 완성형 계산기 | `Win32Calculator_VisualStudio2026` | 유니코드, 오류 처리, 반복 `=`, 단항 연산, 키보드 입력, 반응형 배치 |
| 데이터 모델 | `BookManagerQt/book.h`, Win32 `main.cpp` | `struct Book`, 문자열·논리값으로 도서 상태 표현 |
| Qt GUI | `BookManagerQt` | 위젯, 레이아웃, 시그널·슬롯, JSON 저장, CMake |
| 순수 Win32 GUI | `BookManagerWin32` | ListView, 메시지 기반 이벤트, 동적 배치, 바이너리 저장 |
| 도서관리 기능 | 두 도서관리 프로젝트 | 등록·검색·대출·반납·삭제·자동 저장 |

### 제작 및 학습 방식

`0804` 폴더의 계산기와 도서관리 프로그램은 **AI를 활용하여 만든 프로그램**이다. 필요한 기능과 실행 조건을 AI에 설명하여 코드를 만들고, 생성된 코드를 Visual Studio에서 실행·수정하면서 C++ 문법과 GUI 프로그램의 구조를 학습했다.

AI가 코드를 만들어 주더라도 다음 과정은 직접 확인해야 한다.

1. 각 함수와 변수의 역할을 이해한다.
2. 프로그램을 빌드하고 오류 메시지를 확인한다.
3. 버튼과 입력 기능을 직접 실행해 결과를 시험한다.
4. 잘못된 코드나 원하는 동작과 다른 부분을 수정한다.
5. 수정 전후 코드를 비교하며 사용된 문법을 복습한다.

따라서 이번 작업은 단순히 완성된 코드를 보관하는 것이 아니라, **AI가 생성한 프로그램을 분석·실행·수정하면서 배우는 실습 과정**이다.

이번 학습은 콘솔 프로그램에서 GUI 프로그램으로 넘어가면서 다음 흐름을 익히는 과정이다.

1. 함수를 정의하고 호출한다.
2. 운영체제가 보내는 메시지에 따라 동작하는 GUI 구조를 이해한다.
3. 계산기의 현재 상태를 변수로 관리한다.
4. 구조체와 컨테이너로 여러 데이터를 관리한다.
5. 사용자 입력을 검사하고 업무 규칙을 적용한다.
6. 데이터를 파일로 저장하고 다시 불러온다.

---

## 2. 함수, 매개변수와 반환값

`ConsoleApplication3.cpp`에는 정수를 계산하거나 조건을 판정하는 함수가 있다.

### 2.1 두 값 중 큰 값을 반환하는 함수

```cpp
int bigger(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}
```

- `int`는 함수의 반환 자료형이다.
- `a`, `b`는 함수를 호출할 때 값을 전달받는 매개변수이다.
- `return`은 결과를 호출한 위치로 돌려준다.

```cpp
n = bigger(a, b);
```

위 코드는 `bigger()`를 호출한 뒤 반환값을 `n`에 저장한다.

### 2.2 참 또는 거짓을 반환하는 함수

```cpp
bool dividedBy3(int n) {
    if (n % 3 == 0)
        return true;
    else
        return false;
}
```

- `n % 3`은 `n`을 3으로 나눈 나머지이다.
- 나머지가 0이면 3의 배수이다.
- `bool` 자료형에는 `true` 또는 `false`가 저장된다.

조건식 자체가 이미 참·거짓이므로 다음처럼 간단히 작성할 수도 있다.

```cpp
bool dividedBy3(int n) {
    return n % 3 == 0;
}
```

### 2.3 원본 코드에서 수정해야 할 부분

원본에는 다음 코드가 있다.

```cpp
if (dividedBy3)
```

이 코드는 `dividedBy3` 함수를 **호출한 것이 아니라 함수 자체를 조건으로 사용한 것**이다. 판정하려는 숫자 `n`을 인수로 전달해야 한다.

```cpp
if (dividedBy3(n))
```

괄호와 인수를 작성해야 함수가 실행되고 `true` 또는 `false` 결과를 받을 수 있다.

---

## 3. 콘솔 프로그램과 GUI 프로그램의 차이

콘솔 프로그램은 보통 코드가 위에서 아래로 순서대로 실행된다.

```cpp
cin >> a >> b;
cout << a + b;
```

GUI 프로그램은 사용자가 언제 어떤 버튼을 누를지 알 수 없으므로 **이벤트 중심 방식**으로 동작한다.

```cpp
while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
```

프로그램은 메시지 루프에서 입력을 기다린다. 버튼 클릭, 키보드 입력, 창 크기 변경, 종료 요청 등이 발생하면 Windows가 메시지를 보내고 창 프로시저가 이를 처리한다.

### 3.1 주요 Win32 메시지

| 메시지 | 발생 시점 | 코드에서 하는 일 |
|---|---|---|
| `WM_CREATE` | 창이 생성될 때 | 입력창, 버튼, 목록 등 자식 컨트롤 생성 |
| `WM_COMMAND` | 버튼 클릭이나 입력창 변경 시 | 계산·등록·검색·대출 등의 기능 실행 |
| `WM_SIZE` | 창 크기가 바뀔 때 | 컨트롤의 위치와 크기 재배치 |
| `WM_KEYDOWN` | 특수 키 입력 시 | Enter, Backspace, Esc, Delete 처리 |
| `WM_CHAR` | 문자 키 입력 시 | 숫자와 연산자 키 처리 |
| `WM_CLOSE` | 사용자가 창을 닫을 때 | 저장 후 창 종료 |
| `WM_DESTROY` | 창이 파괴될 때 | `PostQuitMessage()`로 메시지 루프 종료 |

---

## 4. Win32 API로 GUI 만드는 기본 과정

Win32 GUI 프로그램의 공통 실행 과정은 다음과 같다.

### 4.1 창 클래스 등록

```cpp
WNDCLASSA wc = {};
wc.lpfnWndProc = WndProc;
wc.hInstance = hInstance;
wc.lpszClassName = "Calculator";
RegisterClassA(&wc);
```

- 창이 어떤 메시지 처리 함수를 사용할지 지정한다.
- `lpszClassName`은 새 창을 만들 때 사용할 창 클래스 이름이다.

### 4.2 메인 창 생성

```cpp
HWND hwnd = CreateWindowA(
    "Calculator",
    "C++ 계산기",
    WS_OVERLAPPEDWINDOW,
    500, 200, 290, 350,
    nullptr, nullptr, hInstance, nullptr);
```

- `HWND`는 창이나 컨트롤을 식별하는 Windows 핸들이다.
- 창 제목, 스타일, 위치, 크기 등을 전달한다.

### 4.3 자식 컨트롤 생성

```cpp
CreateWindowA("BUTTON", "+", WS_VISIBLE | WS_CHILD,
              20, 100, 40, 30, hwnd, (HMENU)1, nullptr, nullptr);
```

- `BUTTON`, `EDIT`, `STATIC`은 Windows가 제공하는 기본 컨트롤 클래스이다.
- `WS_CHILD`는 메인 창에 속한 자식 컨트롤이라는 뜻이다.
- 버튼의 ID를 통해 어떤 버튼이 클릭되었는지 구분한다.

### 4.4 창 표시와 메시지 루프

```cpp
ShowWindow(hwnd, SW_SHOW);

MSG msg{};
while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
```

창을 화면에 표시하고 프로그램이 종료될 때까지 메시지를 계속 전달한다.

---

## 5. 계산기 개발 단계

`cal.cpp`, `cal1.cpp`, `cal2.cpp`, 완성형 계산기 순으로 기능이 발전한다.

### 5.1 1단계: 두 입력값 계산기 — `cal.cpp`

두 개의 입력창에 숫자를 넣고 사칙연산 버튼을 누르는 방식이다.

```cpp
GetWindowText(hEdit1, buf1, 100);
GetWindowText(hEdit2, buf2, 100);

double a = atof(buf1);
double b = atof(buf2);
```

- `GetWindowText()`로 입력창의 문자열을 읽는다.
- `atof()`로 문자열을 `double` 값으로 변환한다.
- 버튼 ID `1`부터 `4`까지를 `+`, `-`, `*`, `/`로 구분한다.
- 나누기 전에 두 번째 값이 0인지 검사한다.

```cpp
if (b == 0) {
    SetWindowText(hResult, "결과: 0으로 나눌 수 없습니다.");
    return 0;
}
```

### 5.2 2단계: 숫자 버튼 계산기 — `cal1.cpp`

버튼을 눌러 숫자를 표시창에 이어 붙인다.

```cpp
double first = 0;
char op = 0;
bool newNumber = true;
```

| 상태 변수 | 역할 |
|---|---|
| `first` | 첫 번째 피연산자 저장 |
| `op` | 선택한 연산자 저장 |
| `newNumber` | 다음 숫자를 새로 입력할지 결정 |

`AddText()`는 현재 표시 문자열을 읽고 새 숫자를 뒤에 붙인다. 연산자를 누르면 현재 값을 `first`에 저장하고, `=`를 누르면 `Calculate()`가 첫 번째 값과 두 번째 값을 계산한다.

이 단계는 한 번의 이항 연산은 가능하지만 여러 연산을 자연스럽게 이어가는 기능은 제한적이다.

### 5.3 3단계: 연속 계산 — `cal2.cpp`

```cpp
double result = 0;
char operation = 0;
bool newInput = true;
```

`InputOperator()`는 이전 연산이 남아 있고 새 숫자가 입력된 경우 먼저 누적 계산을 실행한다.

```cpp
if (operation != 0 && !newInput) {
    Calculate(current);
} else {
    result = current;
}
```

예를 들어 `10 + 5 × 2 =`를 입력하면 일반 계산기의 표준 모드처럼 입력 순서대로 계산한다.

1. `10 + 5`를 계산해 `15` 저장
2. `15 × 2` 계산
3. 결과 `30` 출력

### 5.4 4단계: 완성형 Win32 계산기

완성형 프로젝트에서는 다음 기능이 추가된다.

- 연속 사칙연산
- 같은 연산을 반복하는 `=` 기능
- 소수점 중복 입력 방지
- 부호 변경, 퍼센트, 제곱, 제곱근, 역수
- CE, C, 백스페이스
- 0으로 나누기와 음수 제곱근 오류 처리
- 키보드 입력
- 창 크기에 따른 버튼 자동 배치
- 유니코드 한글과 특수기호 표시

---

## 6. 계산기의 상태 관리

GUI 계산기는 버튼을 한 번 처리하고 끝나는 것이 아니라 이전 입력 상태를 기억해야 한다.

```cpp
double g_accumulator = 0.0;
double g_lastOperand = 0.0;
wchar_t g_pendingOp = 0;
wchar_t g_lastOp = 0;
bool g_newEntry = true;
bool g_error = false;
```

| 변수 | 의미 |
|---|---|
| `g_accumulator` | 현재까지의 누적 계산 결과 |
| `g_lastOperand` | 반복 `=`에 사용할 마지막 피연산자 |
| `g_pendingOp` | 아직 적용되지 않은 연산자 |
| `g_lastOp` | 반복 `=`에 사용할 마지막 연산자 |
| `g_newEntry` | 새 숫자 입력을 시작할 상태인지 표시 |
| `g_error` | 계산 오류 상태인지 표시 |

### 6.1 입력 처리 함수 분리

```cpp
void ProcessKey(wchar_t key)
```

마우스로 버튼을 클릭한 경우와 키보드로 입력한 경우를 모두 `ProcessKey()`로 전달한다. 입력 경로가 달라도 실제 계산 처리는 한 함수에서 하므로 중복 코드가 줄어든다.

### 6.2 연산 로직 분리

```cpp
bool Apply(double left, wchar_t op, double right, double& result)
```

- 두 피연산자와 연산자를 전달받는다.
- 결과는 참조 매개변수 `result`에 저장한다.
- 계산할 수 있으면 `true`, 오류가 있으면 `false`를 반환한다.
- 나누는 값이 0인지와 계산 결과가 유한한지 검사한다.

이처럼 **입력 처리**, **계산**, **출력 표시**를 함수로 나누면 코드 수정과 오류 확인이 쉬워진다.

### 6.3 반복 `=` 계산

`5 + 2 =`을 실행하면 마지막 연산자 `+`와 피연산자 `2`를 저장한다. 다시 `=`를 누르면 현재 결과 7에 2를 다시 더해 9를 만든다.

---

## 7. 문자 인코딩과 유니코드

초기 계산기 예제는 `CreateWindowA`, `GetWindowTextA`처럼 끝에 `A`가 붙은 ANSI 함수를 사용한다. 완성형 계산기와 도서관리 프로그램은 `W`가 붙은 유니코드 함수를 사용한다.

```cpp
CreateWindowExW(...)
SetWindowTextW(...)
GetWindowTextW(...)
```

### 7.1 문자열 종류

| 문자열 | 문자형 | 예시 |
|---|---|---|
| 좁은 문자열 | `char`, `std::string` | `"Calculator"` |
| 넓은 문자열 | `wchar_t`, `std::wstring` | `L"계산기"` |

한글과 `×`, `÷`, `√`, `⌫` 같은 기호를 안정적으로 표시하려면 유니코드 방식이 유리하다.

### 7.2 UTF-8 파일 저장 변환

Win32 도서관리 프로그램은 화면에서는 `std::wstring`을 사용하고, 파일에는 UTF-8 바이트를 저장한다.

```cpp
WideCharToMultiByte(CP_UTF8, ...)
MultiByteToWideChar(CP_UTF8, ...)
```

- `WideCharToMultiByte()`는 넓은 문자열을 UTF-8로 변환한다.
- `MultiByteToWideChar()`는 UTF-8 데이터를 넓은 문자열로 복원한다.

---

## 8. 도서 데이터 모델

Qt 버전과 Win32 버전 모두 한 권의 도서를 구조체로 표현한다.

```cpp
struct Book {
    문자열 id;
    문자열 title;
    문자열 author;
    문자열 publisher;
    bool borrowed = false;
    문자열 borrower;
    문자열 borrowedDate;
};
```

| 멤버 | 저장 내용 |
|---|---|
| `id` | 중복되지 않는 도서번호 |
| `title` | 도서명 |
| `author` | 저자 |
| `publisher` | 출판사 |
| `borrowed` | 대출 여부 |
| `borrower` | 대출자 이름 |
| `borrowedDate` | 대출 날짜 |

여러 권의 도서는 컨테이너에 저장한다.

```cpp
QVector<Book> books_;       // Qt 버전
std::vector<Book> g_books; // Win32 버전
```

`struct`로 관련 필드를 하나로 묶고 `vector` 계열 컨테이너로 여러 객체를 관리하는 구조이다.

---

## 9. 도서관리 프로그램의 CRUD와 업무 규칙

CRUD는 데이터 프로그램의 기본 동작을 뜻한다.

| 구분 | 의미 | 도서관리 기능 |
|---|---|---|
| Create | 생성 | 새 도서 등록 |
| Read | 조회 | 전체 목록 표시와 검색 |
| Update | 수정 | 대출·반납 상태 변경 |
| Delete | 삭제 | 도서 삭제 |

### 9.1 도서 등록

등록할 때 다음 내용을 검사한다.

- 도서번호, 도서명, 저자는 필수 입력값이다.
- 같은 도서번호를 중복 등록할 수 없다.
- 등록에 성공하면 파일 저장, 입력창 초기화, 목록 새로 고침을 수행한다.

### 9.2 실시간 검색

검색어가 변경될 때마다 전체 도서에서 다음 필드를 검사한다.

- 도서번호
- 도서명
- 저자
- 출판사

대소문자를 구분하지 않고 일부 문자열만 일치해도 검색 결과에 포함한다.

### 9.3 대출

대출 과정에는 다음 규칙이 적용된다.

1. 목록에서 도서를 선택해야 한다.
2. 이미 대출 중인 도서는 다시 대출할 수 없다.
3. 대출자 이름을 입력해야 한다.
4. 대출 상태, 대출자, 현재 날짜를 저장한다.

### 9.4 반납

- 선택한 도서가 실제로 대출 중인지 확인한다.
- `borrowed`를 `false`로 변경한다.
- 대출자와 대출일 문자열을 지운다.

### 9.5 삭제

- 도서를 먼저 선택해야 한다.
- 대출 중인 도서는 삭제하지 못하게 한다.
- 삭제 전에 확인 메시지를 표시한다.

이러한 조건은 단순 버튼 동작이 아니라 프로그램이 반드시 지켜야 하는 **업무 규칙**이다.

---

## 10. 검색 결과와 원본 데이터 연결

검색 후 화면에 보이는 행 번호는 원본 컨테이너의 인덱스와 달라질 수 있다. 예를 들어 전체 데이터의 8번째 도서만 검색 결과 첫 행에 표시될 수 있다.

Qt 버전은 첫 번째 열 아이템의 사용자 데이터에 원본 인덱스를 저장한다.

```cpp
idItem->setData(BookIndexRole, index);
```

Win32 버전은 `LVITEMW::lParam`에 원본 인덱스를 저장한다.

```cpp
item.lParam = static_cast<LPARAM>(index);
```

대출·반납·삭제 시 화면의 행 번호를 그대로 사용하지 않고, 저장해 둔 원본 인덱스를 읽어 실제 `Book` 객체를 찾는다. 정렬이나 검색 기능이 있는 목록에서 매우 중요한 처리이다.

---

## 11. Qt 도서관리 프로그램

### 11.1 프로젝트 구조

| 파일 | 역할 |
|---|---|
| `main.cpp` | `QApplication` 생성, 메인 창 실행 |
| `book.h` | 도서 구조체와 JSON 변환 |
| `mainwindow.h` | 메인 창 클래스와 기능 선언 |
| `mainwindow.cpp` | UI 생성, 이벤트 연결, 도서관리 기능 구현 |
| `CMakeLists.txt` | C++17·Qt Widgets 빌드 설정 |

### 11.2 `QApplication`과 이벤트 루프

```cpp
QApplication application(argc, argv);
MainWindow window;
window.show();
return application.exec();
```

`QApplication`은 Qt GUI 프로그램 전체를 관리한다. `exec()`에서 이벤트 루프를 실행하여 사용자의 입력을 기다린다.

### 11.3 위젯과 레이아웃

- `QLineEdit`: 한 줄 입력창
- `QPushButton`: 버튼
- `QLabel`: 텍스트 표시
- `QTableWidget`: 도서 목록 표
- `QMessageBox`: 경고·확인 메시지
- `QInputDialog`: 대출자 이름 입력 대화상자
- `QStatusBar`: 상태와 저장 경로 표시
- `QHBoxLayout`, `QVBoxLayout`, `QFormLayout`: 위젯 자동 배치

Qt 레이아웃은 창 크기가 바뀌면 위젯의 위치와 크기를 자동으로 조정한다.

### 11.4 시그널과 슬롯

```cpp
connect(addButton_, &QPushButton::clicked,
        this, &MainWindow::addBook);
```

- 버튼이 클릭되면 `clicked` 시그널이 발생한다.
- 연결된 `addBook()` 함수가 실행된다.
- 검색창의 `textChanged` 시그널을 `searchBooks()`에 연결하여 실시간 검색을 구현한다.

### 11.5 JSON 직렬화

```cpp
QJsonObject toJson() const;
static Book fromJson(const QJsonObject &object);
```

- **직렬화**는 객체를 파일에 저장 가능한 형태로 바꾸는 과정이다.
- `toJson()`은 `Book`을 JSON 객체로 변환한다.
- `fromJson()`은 JSON 객체를 다시 `Book`으로 복원한다.
- 전체 도서는 `QJsonArray`에 담아 `books.json`으로 저장한다.

JSON은 사람이 메모장으로 열어 내용을 확인하기 쉽다는 장점이 있다.

### 11.6 종료 이벤트 재정의

```cpp
void MainWindow::closeEvent(QCloseEvent *event)
```

창을 닫기 전에 데이터를 저장한다. 저장에 성공하면 종료하고, 실패하면 종료를 취소하여 데이터 손실을 막는다.

---

## 12. 순수 Win32 도서관리 프로그램

### 12.1 Windows 기본 기능만 사용

Win32 버전은 Qt나 MFC 없이 다음 기술을 사용한다.

- Windows API
- 공용 컨트롤 `ListView`
- C++ 표준 라이브러리
- `std::vector`, `std::wstring`, `std::filesystem`, 파일 스트림

### 12.2 ListView

```cpp
g_bookList = MakeControl(WC_LISTVIEWW, L"",
    LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS | WS_BORDER,
    BookList, WS_EX_CLIENTEDGE);
```

- `LVS_REPORT`는 행과 열이 있는 표 형태를 사용한다.
- `LVS_SINGLESEL`은 한 번에 한 행만 선택하게 한다.
- `LVS_EX_FULLROWSELECT`는 행 전체가 선택되게 한다.
- `LVS_EX_GRIDLINES`는 표의 구분선을 표시한다.

### 12.3 동적 레이아웃

`WM_SIZE` 메시지를 받을 때 `LayoutControls()`를 실행한다.

```cpp
case WM_SIZE:
    LayoutControls(LOWORD(lParam), HIWORD(lParam));
    return 0;
```

현재 창의 너비와 높이를 기준으로 입력창, 목록, 버튼의 크기와 위치를 다시 계산한다. Qt의 자동 레이아웃을 Win32에서는 직접 구현한 셈이다.

### 12.4 바이너리 파일 저장

Win32 버전은 `books.dat`에 다음 순서로 저장한다.

1. 파일 형식 표시값 `BKM1`
2. 저장된 도서 수
3. 각 문자열의 바이트 길이와 UTF-8 데이터
4. 대출 여부
5. 대출자와 대출일

```cpp
constexpr char signature[4] = {'B', 'K', 'M', '1'};
```

불러올 때 서명과 데이터 개수를 검사한다. 문자열 크기와 전체 도서 수도 제한하여 손상된 파일로 인한 지나친 메모리 사용을 방지한다.

### 12.5 저장 위치 결정

```cpp
SHGetFolderPathW(..., CSIDL_APPDATA | CSIDL_FLAG_CREATE, ...)
```

사용자별 AppData 폴더 아래에 `BookManagerWin32/books.dat`를 만든다. 실행 파일이 설치된 폴더가 쓰기 금지 상태여도 사용자 데이터는 정상적으로 저장할 수 있다.

---

## 13. Qt 버전과 Win32 버전 비교

| 항목 | Qt 버전 | 순수 Win32 버전 |
|---|---|---|
| GUI 구성 | Qt Widgets | Windows 기본 컨트롤 |
| 이벤트 처리 | 시그널·슬롯 | Windows 메시지 |
| 레이아웃 | 레이아웃 객체가 자동 처리 | 좌표와 크기를 직접 계산 |
| 문자열 | `QString` | `std::wstring` |
| 목록 | `QTableWidget` | `ListView` |
| 데이터 컨테이너 | `QVector<Book>` | `std::vector<Book>` |
| 저장 형식 | UTF-8 JSON | 자체 바이너리 형식 |
| 빌드 | CMake + Qt 6 | Visual Studio 프로젝트 |
| 추가 설치 | Qt 개발 키트 필요 | Visual Studio C++ 워크로드만 필요 |
| 장점 | 개발이 빠르고 UI 구성이 편리함 | 외부 GUI 라이브러리가 필요 없음 |
| 학습 난이도 | 비교적 구조가 명확함 | Windows 메시지와 API 이해가 더 필요함 |

두 프로젝트의 사용자 기능은 거의 같지만 내부 구현 방식은 크게 다르다. 같은 요구사항을 서로 다른 GUI 기술로 구현해 본 비교 학습 자료라고 볼 수 있다.

---

## 14. 코드 작성 시 보완하면 좋은 부분

### 14.1 함수는 반드시 괄호로 호출

```cpp
if (dividedBy3(n))
```

함수 이름만 쓰지 말고 필요한 인수를 괄호 안에 전달해야 한다.

### 14.2 초기 계산기의 0 나누기 처리

`cal1.cpp`와 `cal2.cpp`에서는 0으로 나눌 때 계산을 수행하지 않지만 사용자에게 오류 메시지를 명확히 보여주지 않는다. 완성형 계산기처럼 오류 상태와 안내 문구를 표시하는 편이 좋다.

### 14.3 입력값 검증

`atof()`는 잘못된 문자열과 숫자 0을 명확히 구분하기 어렵다. `std::stod()`와 예외 처리 또는 별도의 입력 검증을 사용하면 잘못된 입력을 정확하게 안내할 수 있다.

### 14.4 ANSI보다 유니코드 API 사용

새 Windows 프로그램에서는 `CreateWindowW`, `GetWindowTextW`, `std::wstring`처럼 유니코드 방식을 일관되게 사용하는 편이 안전하다.

### 14.5 전역 상태 줄이기

계산기와 Win32 도서관리 프로그램은 많은 GUI 핸들과 데이터를 전역 변수로 관리한다. 작은 학습 예제에는 이해하기 쉽지만 규모가 커지면 클래스로 묶어 상태와 동작을 함께 관리하는 것이 좋다.

### 14.6 원자적 파일 저장

현재 프로그램은 기존 파일을 바로 덮어쓴다. 저장 중 프로그램이 종료되면 파일이 손상될 수 있다. 실제 프로그램에서는 임시 파일에 먼저 저장한 뒤 성공하면 기존 파일과 교체하는 방법이 더 안전하다.

### 14.7 원본과 빌드 결과물 분리

저장소에는 `.exe`, `.obj`, `.pdb`, `.ilk`, `.tlog` 같은 Debug 빌드 결과물이 포함되어 있다. 이 파일들은 다시 빌드할 수 있으므로 일반적으로 `.gitignore`로 제외하고 소스와 프로젝트 설정만 관리한다.

### 14.8 연습 단계별 `main()` 함수

`cal.cpp`, `cal1.cpp`, `cal2.cpp`, `ConsoleApplication3.cpp`에 각각 `main()`이 있는 것은 **서로 다른 연습 코드를 단계별로 실행하기 위한 의도적인 구성**이다.

- `ConsoleApplication3.cpp`: 함수와 반환값 연습
- `cal.cpp`: 입력창 두 개를 사용하는 GUI 계산기 연습
- `cal1.cpp`: 숫자 버튼 방식 계산기 연습
- `cal2.cpp`: 연속 계산 방식 연습

각 파일을 독립적인 예제로 보면 `main()`이 여러 개 있는 것은 문제가 아니다. 다만 Visual Studio에서 실행할 때는 현재 연습할 파일 하나만 빌드 대상으로 지정해야 한다. 여러 파일을 한 번에 빌드 대상으로 포함하면 프로그램 시작점인 `main()`이 중복되어 링커 오류가 발생할 수 있다.

---

## 15. 핵심 복습 문제

1. 함수의 매개변수와 반환값은 각각 어떤 역할을 하는가?
2. `if (dividedBy3)`와 `if (dividedBy3(n))`의 차이는 무엇인가?
3. 콘솔 프로그램과 이벤트 기반 GUI 프로그램의 실행 방식은 어떻게 다른가?
4. `HWND`는 무엇을 나타내는가?
5. `WM_CREATE`, `WM_COMMAND`, `WM_DESTROY`는 언제 발생하는가?
6. Win32 버튼의 ID는 왜 필요한가?
7. 계산기에서 `newInput` 또는 `g_newEntry` 상태가 필요한 이유는 무엇인가?
8. 연속 계산을 위해 누적값과 대기 중인 연산자를 어떻게 관리하는가?
9. ANSI 함수와 유니코드 함수의 차이는 무엇인가?
10. `struct Book`으로 데이터를 묶는 장점은 무엇인가?
11. 도서 등록 시 중복 도서번호를 검사해야 하는 이유는 무엇인가?
12. 대출 중인 도서의 삭제를 막는 코드는 어떤 업무 규칙을 표현하는가?
13. 검색 결과의 행 번호와 원본 컨테이너 인덱스를 따로 연결해야 하는 이유는 무엇인가?
14. 직렬화와 역직렬화는 무엇인가?
15. JSON 저장과 바이너리 저장의 장단점은 무엇인가?
16. Qt의 시그널·슬롯과 Win32의 메시지 방식은 어떻게 다른가?
17. 창 크기가 바뀔 때 Qt와 Win32는 각각 레이아웃을 어떻게 처리하는가?
18. 연습 파일마다 `main()` 함수를 따로 두는 이유와, 빌드할 때 한 파일만 선택해야 하는 이유는 무엇인가?

---

## 16. 최종 요약

0804 학습의 중심은 **C++ 문법을 실제 Windows GUI 프로그램에 적용하는 것**이다.

- AI를 활용해 계산기와 도서관리 프로그램을 만들고, 생성된 코드를 실행·분석·수정하며 학습했다.
- 함수와 `bool` 반환값으로 계산과 판정 코드를 분리했다.
- Win32 메시지 루프를 통해 이벤트 기반 프로그램의 구조를 익혔다.
- 계산기 상태를 변수로 관리하면서 단일 계산에서 연속 계산으로 발전시켰다.
- 한글 처리를 위해 유니코드 문자열과 Win32 `W` 함수를 사용했다.
- `Book` 구조체와 동적 배열을 이용해 여러 도서를 관리했다.
- 등록·검색·대출·반납·삭제 업무 규칙을 함수로 구현했다.
- JSON 또는 바이너리 형식으로 데이터를 저장하고 복원했다.
- 같은 도서관리 요구사항을 Qt와 순수 Win32 방식으로 각각 구현해 두 GUI 기술의 차이를 확인했다.
- 여러 `main()` 함수는 서로 다른 연습 단계를 독립적으로 실행하기 위해 각 예제에 포함되어 있다.

즉, 전날 학습한 클래스·문자열·반복문 등의 기초를 실제 계산기와 도서관리 프로그램으로 확장하면서 **GUI, 상태 관리, 데이터 관리, 파일 저장**을 종합적으로 학습한 내용이다.
