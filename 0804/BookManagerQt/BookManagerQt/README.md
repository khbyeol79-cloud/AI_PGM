# Qt 6 C++ 도서관리 프로그램

Visual Studio와 Qt 6으로 실행할 수 있는 GUI 도서관리 예제입니다.

## 포함 기능

- 도서 등록: 도서번호, 도서명, 저자, 출판사
- 도서 검색: 도서번호, 도서명, 저자, 출판사 통합 검색
- 대출 및 반납: 대출자와 대출일 저장
- 도서 삭제: 대출 중인 도서는 삭제 방지
- JSON 파일 저장: 모든 변경 시 자동 저장, 수동 저장 버튼 제공
- 프로그램 재실행 시 기존 데이터 자동 불러오기

## 필요한 프로그램

1. Visual Studio 2026의 **C++를 사용한 데스크톱 개발** 워크로드
2. Qt 6.x MSVC 64-bit 키트
3. CMake 3.21 이상

Visual Studio 버전에 맞는 Qt MSVC 키트를 설치해야 합니다. 예를 들어 Qt 설치 화면에서 `MSVC 2022 64-bit`처럼 현재 Visual Studio와 호환되는 키트를 선택합니다.

## Visual Studio에서 실행하기

1. Visual Studio를 실행합니다.
2. **파일 > 열기 > 폴더**를 선택합니다.
3. 이 `BookManagerQt` 폴더를 선택합니다.
4. Visual Studio가 `CMakeLists.txt`를 인식하고 구성을 마칠 때까지 기다립니다.
5. 상단 시작 항목에서 `BookManagerQt.exe`를 선택합니다.
6. **디버그 > 디버깅하지 않고 시작**을 누릅니다.

Qt를 찾지 못한다는 오류가 나오면 Visual Studio의 CMake 설정에서 `CMAKE_PREFIX_PATH`를 Qt 설치 경로로 지정합니다. 예시는 다음과 같습니다.

```text
C:/Qt/6.8.3/msvc2022_64
```

설치한 Qt 버전과 키트 이름에 맞게 경로를 변경해야 합니다.

## 저장 파일

데이터는 `books.json`에 UTF-8 JSON 형식으로 저장됩니다. 정확한 저장 위치는 프로그램 실행 후 아래쪽 상태 표시줄 또는 **파일 저장** 버튼을 눌러 확인할 수 있습니다.

Windows에서는 보통 아래와 같은 사용자별 앱 데이터 폴더에 생성됩니다.

```text
C:\\Users\\사용자명\\AppData\\Roaming\\BookManagerExample\\BookManagerQt\\books.json
```

## 사용 방법

1. 필수 입력란인 도서번호, 도서명, 저자를 입력하고 **도서 등록**을 누릅니다.
2. 검색창에 단어를 입력하면 목록이 즉시 필터링됩니다.
3. 목록에서 한 행을 선택하고 **선택 도서 대출**을 누른 뒤 대출자 이름을 입력합니다.
4. 대출된 행을 선택하고 **선택 도서 반납**을 누르면 반납됩니다.
5. 대출되지 않은 행을 선택하고 **선택 도서 삭제**를 누르면 확인 후 삭제됩니다.

## 프로젝트 파일

- `main.cpp`: 프로그램 시작점
- `book.h`: 도서 데이터 구조와 JSON 변환
- `mainwindow.h`, `mainwindow.cpp`: GUI 및 모든 기능
- `CMakeLists.txt`: Visual Studio/CMake 빌드 설정
