# Python 자료형 정리 - 리스트(List), 튜플(Tuple), 집합(Set), 딕셔너리(Dictionary)

---

# 1. 리스트 (List)

## 특징
- 여러 개의 데이터를 순서대로 저장
- **순서(O)가 있음**
- **중복(O) 허용**
- **수정(O) 가능(Mutable)**

```python
a = [10, 20, 30, 40]
print(a)
```
출력
```
[10, 20, 30, 40]
```

---

## 요소 접근

```python
a = [10, 20, 30, 40]

print(a[0])
print(a[2])
print(a[-1])
```
출력
```
10
30
40
```

---

## 값 변경

```python
a = [10, 20, 30]

a[1] = 200

print(a)
```
출력
```
[10, 200, 30]
```

---

## 자주 사용하는 함수

### append()

맨 뒤에 추가

```python
a = [1,2,3]
a.append(4)

print(a)
```

```
[1,2,3,4]
```

---

### insert()

원하는 위치에 삽입

```python
a=[1,2,3]
a.insert(1,100)

print(a)
```

```
[1,100,2,3]
```

---

### remove()

값 삭제

```python
a=[1,2,3]

a.remove(2)

print(a)
```

```
[1,3]
```

---

### pop()

마지막 요소 삭제 후 반환

```python
a=[10,20,30]

x=a.pop()

print(x)
print(a)
```

```
30
[10,20]
```

---

### sort()

오름차순 정렬

```python
a=[5,2,8,1]

a.sort()

print(a)
```

```
[1,2,5,8]
```

---

### reverse()

순서 뒤집기

```python
a=[1,2,3]

a.reverse()

print(a)
```

```
[3,2,1]
```

---

### len()

길이

```python
a=[1,2,3]

print(len(a))
```

```
3
```

---

# 2. 튜플 (Tuple)

## 특징

- 순서(O)
- 중복(O)
- 수정(X) (Immutable)

```python
t=(10,20,30)

print(t)
```

```
(10,20,30)
```

---

## 요소 접근

```python
t=(10,20,30)

print(t[1])
```

```
20
```

---

## 수정 불가능

```python
t=(10,20,30)

t[0]=100
```

오류 발생

```
TypeError
```

---

## 튜플 사용하는 이유

- 데이터 보호
- 속도가 리스트보다 조금 빠름
- 변경되면 안 되는 데이터 저장

예)

```python
days=("월","화","수","목","금")
```

---

# 3. 집합 (Set)

## 특징

- 순서(X)
- 중복(X)
- 수정(O)

```python
s={1,2,3,4}

print(s)
```

---

## 중복 제거

```python
s={1,2,2,3,3,4}

print(s)
```

출력

```
{1,2,3,4}
```

---

## add()

추가

```python
s={1,2,3}

s.add(4)

print(s)
```

---

## remove()

삭제

```python
s={1,2,3}

s.remove(2)

print(s)
```

---

## 집합 연산

### 합집합

```python
a={1,2,3}
b={3,4,5}

print(a|b)
```

```
{1,2,3,4,5}
```

---

### 교집합

```python
print(a&b)
```

```
{3}
```

---

### 차집합

```python
print(a-b)
```

```
{1,2}
```

---

# 4. 딕셔너리 (Dictionary)

## 특징

- Key : Value 형태
- 순서(O) (Python 3.7 이상)
- Key는 중복 불가
- Value는 중복 가능

```python
student={
    "name":"홍길동",
    "age":20,
    "major":"AI"
}

print(student)
```

---

## 값 가져오기

```python
print(student["name"])
print(student["age"])
```

출력

```
홍길동
20
```

---

## 값 수정

```python
student["age"]=25

print(student)
```

---

## 값 추가

```python
student["grade"]="A"

print(student)
```

---

## 삭제

```python
del student["age"]

print(student)
```

---

## 주요 함수

### keys()

```python
print(student.keys())
```

---

### values()

```python
print(student.values())
```

---

### items()

```python
print(student.items())
```

---

### get()

```python
print(student.get("name"))
```

---

# 자료형 비교

|구분|리스트(List)|튜플(Tuple)|집합(Set)|딕셔너리(Dictionary)|
|----|------------|-----------|---------|--------------------|
|순서|O|O|X|O (Python 3.7+)|
|중복|O|O|X|Key(X), Value(O)|
|수정|O|X|O|O|
|인덱싱|O|O|X|Key 사용|
|사용기호|[]|()|{}|{key:value}|

---

# 언제 사용할까?

### 리스트(List)

- 학생 목록
- 점수 목록
- 파일 목록
- 이미지 데이터

```python
scores=[90,80,70]
```

---

### 튜플(Tuple)

- 좌표
- RGB 색상
- 변경되면 안 되는 데이터

```python
point=(100,200)
```

---

### 집합(Set)

- 중복 제거
- 교집합
- 합집합

```python
numbers={1,2,2,3}
```

---

### 딕셔너리(Dictionary)

- 회원 정보
- 학생 정보
- JSON 데이터

```python
student={
    "name":"Kim",
    "age":22
}
```

---

# 한눈에 암기하기

```
리스트(List)
    순서 O
    중복 O
    수정 O

튜플(Tuple)
    순서 O
    중복 O
    수정 X

집합(Set)
    순서 X
    중복 X
    수정 O

딕셔너리(Dictionary)
    Key : Value
    Key 중복 X
    Value 중복 O
```

---

# 자주 나오는 함수

## 리스트

- append()
- insert()
- remove()
- pop()
- sort()
- reverse()
- len()

## 집합

- add()
- remove()
- union()
- intersection()
- difference()

## 딕셔너리

- keys()
- values()
- items()
- get()
- update()
- pop()

---

# 요약

|자료형|대표 사용 목적|
|-------|--------------|
|List|순서가 있는 데이터 저장|
|Tuple|변경되면 안 되는 데이터 저장|
|Set|중복 제거 및 집합 연산|
|Dictionary|Key-Value 형태 데이터 관리|
