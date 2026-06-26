# 파이썬 컨테이너(Container)와 if문 정리

## 1. 컨테이너(Container)란?

여러 개의 데이터를 하나의 변수에 저장하는 자료형입니다.

대표적인 컨테이너 - 리스트(List) - 튜플(Tuple) - 딕셔너리(Dictionary) -
집합(Set)

## 2. 리스트(List)

``` python
numbers = [10, 20, 30]
fruits = ["사과", "바나나", "포도"]
```

``` python
print(fruits[0])
print(fruits[-1])
```

``` python
fruits.append("딸기")
fruits.remove("바나나")
```

## 3. 튜플(Tuple)

``` python
t = (10, 20, 30)
```

-   수정 불가능(Immutable)
-   읽기 전용 데이터 저장

## 4. 딕셔너리(Dictionary)

``` python
student = {
    "name": "홍길동",
    "age": 20
}

print(student["name"])
```

## 5. 집합(Set)

``` python
s = {1, 2, 3}
s.add(4)
```

-   중복 허용 안 함
-   순서 없음

## 6. if문

``` python
if 조건식:
    실행문
```

예제

``` python
age = 20

if age >= 19:
    print("성인입니다.")
```

## 7. if \~ else

``` python
age = 15

if age >= 19:
    print("성인")
else:
    print("미성년자")
```

## 8. if \~ elif \~ else

``` python
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

## 9. 논리 연산자

``` python
and
or
not
```

``` python
age = 20
score = 80

if age >= 19 and score >= 60:
    print("합격")
```

## 10. 멤버십 연산자

``` python
fruits = ["사과", "바나나", "포도"]

if "사과" in fruits:
    print("사과가 있습니다.")
```

## 11. 실습 문제

1.  정수 하나를 입력받아 양수인지 음수인지 출력하세요.
2.  점수를 입력받아 A, B, C, F 학점을 출력하세요.
3.  과일 리스트에 '사과'가 있는지 검사하세요.
4.  딕셔너리에 저장된 이름과 나이를 출력하세요.

## 핵심 정리

-   List : 순서 O, 수정 O
-   Tuple : 순서 O, 수정 X
-   Dictionary : Key-Value 저장
-   Set : 중복 X, 순서 X
-   if, if\~else, if~elif~else
-   and, or, not
-   in, not in
