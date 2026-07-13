# Python 제어문 정리 - if, for, while, lambda

---

# 1. if 문 (조건문)

## 특징

- 조건에 따라 다른 코드를 실행
- 조건이 참(True)이면 실행
- 거짓(False)이면 실행하지 않음

기본 형태

```python
if 조건:
    실행문
```

예제

```python
age = 20

if age >= 19:
    print("성인입니다.")
```

출력

```
성인입니다.
```

---

## if - else

조건이 거짓일 때 실행

```python
score = 70

if score >= 80:
    print("합격")
else:
    print("불합격")
```

출력

```
불합격
```

---

## if - elif - else

여러 조건 검사

```python
score = 85

if score >= 90:
    print("A")
elif score >= 80:
    print("B")
elif score >= 70:
    print("C")
else:
    print("F")
```

출력

```
B
```

---

## 논리 연산자

### and

모든 조건이 참

```python
age = 20
money = 10000

if age >= 19 and money >= 5000:
    print("영화 관람 가능")
```

---

### or

하나만 참이어도 참

```python
if age >= 19 or money >= 5000:
    print("조건 만족")
```

---

### not

참과 거짓 반전

```python
x = False

if not x:
    print("참입니다.")
```

---

## 삼항 연산자

한 줄로 조건 표현

```python
score = 90

result = "합격" if score >= 80 else "불합격"

print(result)
```

---

# 2. for 문 (반복문)

## 특징

- 정해진 횟수만큼 반복
- 리스트, 문자열, 튜플 등 반복 가능 객체(Iterable)에 사용

기본 형태

```python
for 변수 in 반복객체:
    실행문
```

---

## 리스트 반복

```python
numbers = [10,20,30]

for n in numbers:
    print(n)
```

출력

```
10
20
30
```

---

## 문자열 반복

```python
for ch in "Python":
    print(ch)
```

---

## range()

### range(5)

```python
for i in range(5):
    print(i)
```

출력

```
0
1
2
3
4
```

---

### range(1,6)

```python
for i in range(1,6):
    print(i)
```

출력

```
1
2
3
4
5
```

---

### range(1,10,2)

```python
for i in range(1,10,2):
    print(i)
```

출력

```
1
3
5
7
9
```

---

## 중첩 반복문

```python
for i in range(3):
    for j in range(2):
        print(i, j)
```

---

## break

반복 종료

```python
for i in range(10):
    if i == 5:
        break
    print(i)
```

출력

```
0
1
2
3
4
```

---

## continue

현재 반복만 건너뛰기

```python
for i in range(5):
    if i == 2:
        continue
    print(i)
```

출력

```
0
1
3
4
```

---

# 3. while 문 (반복문)

## 특징

- 조건이 참인 동안 반복
- 반복 횟수가 정해지지 않았을 때 사용

기본 형태

```python
while 조건:
    실행문
```

---

## 기본 예제

```python
i = 1

while i <= 5:
    print(i)
    i += 1
```

출력

```
1
2
3
4
5
```

---

## 무한 반복

```python
while True:
    print("실행")
```

종료하려면 `break` 사용

---

## break

```python
i = 1

while True:
    print(i)

    if i == 5:
        break

    i += 1
```

---

## continue

```python
i = 0

while i < 5:
    i += 1

    if i == 3:
        continue

    print(i)
```

출력

```
1
2
4
5
```

---

# 4. lambda 함수

## 특징

- 이름 없는 함수(익명 함수)
- 한 줄로 작성
- 간단한 함수 작성 시 사용

기본 형태

```python
lambda 매개변수 : 반환값
```

---

## 일반 함수

```python
def add(a, b):
    return a + b

print(add(3,5))
```

---

## lambda 함수

```python
add = lambda a, b: a + b

print(add(3,5))
```

출력

```
8
```

---

## 매개변수 1개

```python
square = lambda x: x*x

print(square(5))
```

출력

```
25
```

---

## 조건식 사용

```python
result = lambda x: "짝수" if x % 2 == 0 else "홀수"

print(result(10))
```

출력

```
짝수
```

---

## map()과 lambda

리스트의 모든 요소에 함수 적용

```python
numbers = [1,2,3,4]

result = list(map(lambda x: x*2, numbers))

print(result)
```

출력

```
[2,4,6,8]
```

---

## filter()와 lambda

조건에 맞는 값만 선택

```python
numbers = [1,2,3,4,5,6]

result = list(filter(lambda x: x%2==0, numbers))

print(result)
```

출력

```
[2,4,6]
```

---

## sorted()와 lambda

기준을 지정하여 정렬

```python
students = [
    ("Kim",90),
    ("Lee",70),
    ("Park",80)
]

students.sort(key=lambda x:x[1])

print(students)
```

출력

```
[('Lee',70), ('Park',80), ('Kim',90)]
```

---

# 반복문 비교

|구분|for|while|
|----|---|-----|
|반복 횟수|정해져 있음|정해져 있지 않음|
|사용 대상|리스트, 문자열, range() 등|조건식|
|종료 조건|반복 객체 끝|조건이 False|

---

# break / continue

|명령어|설명|
|------|----|
|break|반복문 즉시 종료|
|continue|현재 반복만 건너뛰고 다음 반복 실행|

---

# lambda 특징

- 함수 이름 없이 작성
- return을 쓰지 않음
- 한 줄만 작성 가능
- 간단한 계산에 적합
- map(), filter(), sorted()와 자주 사용

---

# 언제 사용할까?

### if

- 로그인 확인
- 점수 판별
- 메뉴 선택

```python
if score >= 80:
    print("합격")
```

---

### for

- 학생 목록 출력
- 파일 읽기
- 리스트 순회

```python
for item in items:
    print(item)
```

---

### while

- 게임 반복
- 메뉴 반복
- 입력 받을 때

```python
while True:
    menu = input("입력 : ")
```

---

### lambda

- 간단한 계산
- 정렬 기준 지정
- map(), filter()에서 사용

```python
lambda x: x*2
```

---

# 한눈에 암기하기

```
if
    조건에 따라 실행

for
    정해진 횟수 반복

while
    조건이 참인 동안 반복

lambda
    한 줄짜리 익명 함수
```

---

# 요약

|문법|대표 사용 목적|
|----|--------------|
|if|조건에 따라 실행|
|for|정해진 횟수 반복|
|while|조건이 참인 동안 반복|
|lambda|간단한 익명 함수 작성|
