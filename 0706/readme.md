# Python 클래스(Class) 및 주요 라이브러리 정리

---

# 1. 클래스(Class)

## 클래스(Class)란?

클래스(Class)는 **객체(Object)를 만들기 위한 설계도(틀)** 입니다.

예를 들어,

- 클래스 → 자동차 설계도
- 객체 → 실제 자동차

파이썬은 객체지향 프로그래밍(OOP)을 지원하며, 클래스를 이용하여 객체를 생성합니다.

---

## 객체(Object)

클래스로부터 만들어진 실제 데이터입니다.

```python
class Person:
    pass

p1 = Person()
p2 = Person()
```

```
Person 클래스
      │
      ▼
객체 생성
      │
 ┌────┴────┐
 ▼         ▼
p1        p2
```

---

## 클래스 정의

기본 형태

```python
class 클래스이름:
    내용
```

예제

```python
class Person:
    pass
```

---

## 생성자 (__init__)

객체가 생성될 때 자동으로 실행되는 함수입니다.

```python
class Person:

    def __init__(self):
        print("객체 생성")
```

객체 생성

```python
p = Person()
```

출력

```
객체 생성
```

---

## self

현재 객체 자신을 의미합니다.

```python
class Person:

    def hello(self):
        print("안녕하세요")
```

호출

```python
p = Person()

p.hello()
```

---

## 멤버 변수

```python
class Person:

    def __init__(self,name):
        self.name = name
```

사용

```python
p = Person("홍길동")

print(p.name)
```

출력

```
홍길동
```

---

## 메서드(Method)

클래스 안에 정의된 함수입니다.

```python
class Calculator:

    def add(self,a,b):
        return a+b

c = Calculator()

print(c.add(3,5))
```

출력

```
8
```

---

## 클래스 구조

```text
Class
 │
 ├── 변수(Attribute)
 │
 └── 메서드(Method)
```

---

## 클래스 사용하는 이유

- 코드 재사용
- 객체 관리
- 프로그램 구조화
- 유지보수 쉬움

---

# 2. tkinter

## tkinter란?

Python의 **GUI(그래픽 사용자 인터페이스)** 를 만드는 기본 라이브러리입니다.

버튼, 창, 입력창 등을 만들 수 있습니다.

---

## 기본 사용

```python
import tkinter as tk

window = tk.Tk()

window.mainloop()
```

---

## 버튼 만들기

```python
import tkinter as tk

window = tk.Tk()

btn = tk.Button(window,text="클릭")
btn.pack()

window.mainloop()
```

---

## Label

문자 출력

```python
label = tk.Label(window,text="Hello")
```

---

## Entry

텍스트 입력창

```python
entry = tk.Entry(window)
```

---

## 주요 위젯

|위젯|기능|
|----|----|
|Tk()|메인 창|
|Label|문자 출력|
|Button|버튼|
|Entry|입력창|
|Text|여러 줄 입력|
|Frame|영역 분할|
|Canvas|그림 그리기|

---

# 3. math

## math란?

수학 계산을 위한 표준 라이브러리입니다.

```python
import math
```

---

## 자주 사용하는 함수

### 제곱근

```python
math.sqrt(25)
```

결과

```
5
```

---

### 거듭제곱

```python
math.pow(2,3)
```

결과

```
8
```

---

### 올림

```python
math.ceil(3.2)
```

결과

```
4
```

---

### 내림

```python
math.floor(3.9)
```

결과

```
3
```

---

### 원주율

```python
math.pi
```

결과

```
3.141592...
```

---

### 삼각함수

```python
math.sin()
math.cos()
math.tan()
```

---

## 자주 사용하는 함수

- sqrt()
- pow()
- ceil()
- floor()
- fabs()
- factorial()
- sin()
- cos()
- tan()
- pi

---

# 4. NumPy

## NumPy란?

NumPy(Numerical Python)는 **수치 계산과 행렬 연산을 위한 라이브러리**입니다.

인공지능, 머신러닝, 데이터 분석에서 가장 많이 사용됩니다.

```python
import numpy as np
```

---

## 배열 생성

```python
import numpy as np

a = np.array([1,2,3])

print(a)
```

---

## 2차원 배열

```python
a = np.array([
    [1,2],
    [3,4]
])
```

---

## 배열 모양

```python
print(a.shape)
```

결과

```
(2,2)
```

---

## 배열 크기

```python
print(a.size)
```

---

## 자료형

```python
print(a.dtype)
```

---

## 0으로 초기화

```python
np.zeros((3,3))
```

---

## 1로 초기화

```python
np.ones((2,2))
```

---

## 연속된 숫자

```python
np.arange(1,10)
```

---

## 평균

```python
np.mean(a)
```

---

## 합계

```python
np.sum(a)
```

---

## 최대값

```python
np.max(a)
```

---

## 최소값

```python
np.min(a)
```

---

## 배열 연산

```python
a=np.array([1,2,3])

print(a*2)
```

결과

```
[2 4 6]
```

---

# NumPy 사용하는 이유

- 빠른 계산
- 행렬 연산
- 벡터 계산
- 머신러닝 필수 라이브러리

---

# 한눈에 정리

## 클래스(Class)

```
객체를 만들기 위한 설계도

class
↓

객체 생성

↓

메서드 사용
```

---

## tkinter

```
GUI 프로그램 제작

창
버튼
입력창
레이블
```

---

## math

```
수학 계산

sqrt()
pow()
ceil()
floor()
pi
```

---

## NumPy

```
수치 계산

array()

행렬 연산

평균
합계
최대
최소
```

---

# 요약

|항목|용도|
|----|----|
|Class|객체지향 프로그래밍(OOP)|
|tkinter|GUI 프로그램 제작|
|math|수학 계산|
|NumPy|배열 및 수치 계산, 머신러닝|
