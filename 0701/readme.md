# Python 함수(Function) 정의 정리

---

# 1. 함수(Function)란?

함수(Function)는 **특정 작업을 수행하는 코드의 묶음**입니다.

같은 코드를 여러 번 작성하지 않고, **한 번 만들어 여러 번 사용할 수 있습니다.**

## 함수를 사용하는 이유

- 코드의 재사용
- 코드 길이 감소
- 유지보수 용이
- 프로그램 구조를 이해하기 쉬움

예)

```python
def hello():
    print("안녕하세요.")
```

---

# 2. 함수 정의

기본 형태

```python
def 함수이름(매개변수):
    실행문
```

예)

```python
def hello():
    print("Hello Python")
```

함수 실행

```python
hello()
```

출력

```
Hello Python
```

---

# 3. 함수 호출(Call)

함수는 정의만 하면 실행되지 않습니다.

반드시 호출해야 합니다.

```python
def hello():
    print("안녕하세요.")

hello()
hello()
```

출력

```
안녕하세요.
안녕하세요.
```

---

# 4. 매개변수(Parameter)

함수에 전달받는 값입니다.

```python
def hello(name):
    print(name)
```

호출

```python
hello("홍길동")
```

출력

```
홍길동
```

---

# 5. 인수(Argument)

함수를 호출할 때 전달하는 실제 값입니다.

```python
def add(a,b):
    print(a+b)

add(10,20)
```

|구분|내용|
|----|----|
|매개변수(Parameter)|a, b|
|인수(Argument)|10, 20|

---

# 6. return

함수의 결과를 반환합니다.

```python
def add(a,b):
    return a+b

result = add(3,5)

print(result)
```

출력

```
8
```

---

# 7. return이 없는 함수

```python
def hello():
    print("Python")
```

호출

```python
hello()
```

출력

```
Python
```

실제로 반환되는 값

```python
print(hello())
```

출력

```
Python
None
```

---

# 8. 여러 값 반환

파이썬은 여러 값을 반환할 수 있습니다.

```python
def calc(a,b):
    return a+b, a-b

x,y = calc(10,5)

print(x)
print(y)
```

출력

```
15
5
```

---

# 9. 기본값(Default Parameter)

매개변수에 기본값을 지정할 수 있습니다.

```python
def hello(name="Python"):
    print(name)
```

호출

```python
hello()
hello("AI")
```

출력

```
Python
AI
```

---

# 10. 키워드 인수

매개변수 이름을 지정하여 전달

```python
def student(name,age):
    print(name)
    print(age)

student(age=20,name="Kim")
```

출력

```
Kim
20
```

---

# 11. 지역 변수(Local Variable)

함수 안에서만 사용할 수 있는 변수

```python
def test():
    x=10
    print(x)

test()
```

함수 밖에서는

```python
print(x)
```

오류 발생

```
NameError
```

---

# 12. 전역 변수(Global Variable)

함수 밖에서 선언한 변수

```python
x=100

def test():
    print(x)

test()
```

출력

```
100
```

---

# 13. global 키워드

함수 안에서 전역변수를 수정

```python
x=10

def test():
    global x
    x=20

test()

print(x)
```

출력

```
20
```

---

# 14. 함수 안에서 함수 호출

```python
def hello():
    print("Hello")

def main():
    hello()

main()
```

출력

```
Hello
```

---

# 15. main() 함수

프로그램의 시작 역할

```python
def main():
    print("프로그램 시작")

main()
```

실무에서는

```python
if __name__=="__main__":
    main()
```

형태를 많이 사용합니다.

---

# 16. 함수 작성 예제

### 더하기

```python
def add(a,b):
    return a+b

print(add(3,5))
```

---

### 큰 수 구하기

```python
def max_num(a,b):
    if a>b:
        return a
    else:
        return b

print(max_num(10,20))
```

---

### 짝수 판별

```python
def even(n):
    if n%2==0:
        return True
    else:
        return False

print(even(8))
```

---

### 원의 넓이

```python
def circle(r):
    return 3.14*r*r

print(circle(5))
```

---

# 함수 실행 과정

```text
함수 정의
    │
    ▼
함수 호출
    │
    ▼
매개변수 전달
    │
    ▼
실행
    │
    ▼
return
    │
    ▼
호출한 곳으로 결과 반환
```

---

# 함수 관련 용어

|용어|설명|
|----|----|
|def|함수 정의|
|Call|함수 호출|
|Parameter|매개변수|
|Argument|인수|
|return|결과 반환|
|Local Variable|지역 변수|
|Global Variable|전역 변수|

---

# 함수 사용 장점

- 코드 재사용
- 중복 제거
- 가독성 향상
- 유지보수 쉬움
- 프로그램 구조화

---

# 한눈에 암기하기

```
def
    함수 정의

()

    함수 호출

Parameter
    매개변수

Argument
    전달값

return
    결과 반환

main()
    프로그램 시작 함수
```

---

# 요약

|문법|설명|
|----|----|
|def|함수 정의|
|함수이름()|함수 호출|
|매개변수|함수에서 받는 값|
|인수|함수에 전달하는 실제 값|
|return|결과 반환|
|global|전역 변수 수정|
|main()|프로그램 시작 함수|
