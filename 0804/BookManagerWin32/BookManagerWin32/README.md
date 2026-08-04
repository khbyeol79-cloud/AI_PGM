# 추가 프로그램이 필요 없는 C++ 도서관리 프로그램

이 프로젝트는 Qt, MFC, .NET, 외부 라이브러리를 사용하지 않습니다. Windows에 기본 포함된 Win32 API와 C++ 표준 라이브러리만 사용합니다.

## 필요한 구성

- Visual Studio 2026
- Visual Studio 설치 관리자의 **C++를 사용한 데스크톱 개발** 워크로드

별도로 Qt나 다른 GUI 프로그램을 설치할 필요가 없습니다. Windows SDK는 위 워크로드에 포함됩니다.

## 실행 방법

1. `BookManagerWin32.sln`을 더블클릭합니다.
2. Visual Studio가 프로젝트 대상 변경을 묻는 경우 현재 설치된 Windows SDK와 도구 집합을 선택합니다.
3. 상단 구성을 `Debug`, 플랫폼을 `x64`로 둡니다.
4. `Ctrl+F5`를 눌러 실행합니다.

## 기능

- 도서 등록: 도서번호, 도서명, 저자, 출판사
- 실시간 검색: 도서번호, 도서명, 저자, 출판사
- 대출: 목록에서 도서를 선택하고 대출자 입력 후 대출
- 반납: 대출 중인 도서를 선택해 반납
- 삭제: 대출 중이 아닌 도서만 삭제
- 자동 저장: 등록, 대출, 반납, 삭제 및 종료 시 저장
- 수동 저장: 파일 저장 버튼 제공
- 재실행 시 저장한 데이터 자동 불러오기

## 데이터 파일 위치

일반적으로 다음 위치에 `books.dat` 파일이 만들어집니다.

```text
C:\Users\사용자명\AppData\Roaming\BookManagerWin32\books.dat
```

프로그램 화면 아래쪽에서도 정확한 저장 위치를 확인할 수 있습니다.

## 소스 구성

- `main.cpp`: GUI, 도서 데이터, 검색, 대출·반납·삭제, 파일 저장 전체 코드
- `BookManagerWin32.sln`: Visual Studio 솔루션
- `BookManagerWin32.vcxproj`: Visual Studio C++ 프로젝트 설정
