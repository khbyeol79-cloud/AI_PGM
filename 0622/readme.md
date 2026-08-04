# Python 문자열(String)과 인덱싱(Indexing) 정리

---

# 1. 문자열(String)

## 특징

- 문자들의 집합
- 작은따옴표('') 또는 큰따옴표("")로 표현
- **순서(O)**
- **중복(O)**
- **수정(X) (Immutable, 불변 객체)**

```python
name = "Python"
language = 'AI'

print(name)
print(language)
```

출력

```
Python
AI
```

---

## 여러 줄 문자열

### 큰따옴표 3개

```python
text = """
안녕하세요.
파이썬입니다.
"""

print(text)
```

---

### 작은따옴표 3개

```python
text = '''
Hello
Python
'''
```

---

# 2. 문자열 인덱싱(Indexing)

## 특징

- 문자열은 0부터 시작
- 음수 인덱스 사용 가능

```python
word = "Python"
```

|문자|P|y|t|h|o|n|
|----|--|--|--|--|--|--|
|인덱스|0|1|2|3|4|5|
|음수|-6|-5|-4|-3|-2|-1|

---

## 인덱싱

```python
word = "Python"

print(word[0])
print(word[1])
print(word[-1])
```

출력

```
P
y
n
```

---

# 3. 슬라이싱(Slicing)

## 기본 형태

```python
문자열[시작:끝]
```

- 시작 포함
- 끝 제외

```python
word = "Python"

print(word[0:2])
print(word[2:5])
```

출력

```
Py
tho
```

---

## 처음부터

```python
print(word[:3])
```

출력

```
Pyt
```

---

## 끝까지

```python
print(word[2:])
```

출력

```
thon
```

---

## 전체 복사

```python
print(word[:])
```

출력

```
Python
```

---

## 음수 인덱스 슬라이싱

```python
print(word[-3:])
```

출력

```
hon
```

---

## 간격 지정

기본 형태

```python
문자열[시작:끝:간격]
```

```python
word = "Python"

print(word[::2])
```

출력

```
Pto
```

---

## 문자열 뒤집기

```python
print(word[::-1])
```

출력

```
nohtyP
```

---

# 4. 문자열 연결

```python
a = "Hello"
b = "Python"

print(a + " " + b)
```

출력

```
Hello Python
```

---

# 5. 문자열 반복

```python
print("Python" * 3)
```

출력

```
PythonPythonPython
```

---

# 6. 문자열 길이

```python
text = "Python"

print(len(text))
```

출력

```
6
```

---

# 7. 문자열 포함 여부

```python
text = "Python"

print("P" in text)
print("A" in text)
```

출력

```
True
False
```

---

# 8. 자주 사용하는 문자열 함수

## upper()

모두 대문자

```python
text = "python"

print(text.upper())
```

출력

```
PYTHON
```

---

## lower()

모두 소문자

```python
text = "PYTHON"

print(text.lower())
```

출력

```
python
```

---

## title()

각 단어 첫 글자만 대문자

```python
text = "python programming"

print(text.title())
```

출력

```
Python Programming
```

---

## strip()

앞뒤 공백 제거

```python
text = "   Python   "

print(text.strip())
```

출력

```
Python
```

---

## replace()

문자 변경

```python
text = "Python"

print(text.replace("Python","AI"))
```

출력

```
AI
```

---

## split()

문자열 나누기

```python
text = "apple banana orange"

print(text.split())
```

출력

```
['apple', 'banana', 'orange']
```

---

## join()

문자열 합치기

```python
words = ["Python","AI","ML"]

print("-".join(words))
```

출력

```
Python-AI-ML
```

---

## find()

문자의 위치 반환

```python
text = "Python"

print(text.find("t"))
```

출력

```
2
```

찾지 못하면

```
-1
```

---

## count()

문자 개수

```python
text = "banana"

print(text.count("a"))
```

출력

```
3
```

---

## startswith()

시작 문자 확인

```python
text = "Python"

print(text.startswith("Py"))
```

출력

```
True
```

---

## endswith()

끝 문자 확인

```python
print(text.endswith("on"))
```

출력

```
True
```

---

# 9. 문자열 포매팅

## %

```python
name = "Kim"

print("이름은 %s 입니다." % name)
```

---

## format()

```python
name = "Kim"

print("이름은 {} 입니다.".format(name))
```

---

## f-string (가장 많이 사용)

```python
name = "Kim"
age = 20

print(f"이름은 {name}, 나이는 {age}세입니다.")
```

출력

```
이름은 Kim, 나이는 20세입니다.
```

---

# 문자열은 수정할 수 없다

잘못된 예

```python
text = "Python"

text[0] = "J"
```

오류

```
TypeError
```

올바른 방법

```python
text = "Python"

text = "J" + text[1:]

print(text)
```

출력

```
Jython
```

---

# 문자열과 리스트 차이

|구분|문자열(String)|리스트(List)|
|----|--------------|------------|
|순서|O|O|
|중복|O|O|
|수정|X|O|
|인덱싱|O|O|
|슬라이싱|O|O|

---

# 한눈에 암기하기

```
문자열(String)

순서 O
중복 O
수정 X

인덱싱
[]
슬라이싱
[:]

0부터 시작
음수 인덱스 가능
```

---

# 자주 사용하는 함수

- len()
- upper()
- lower()
- title()
- strip()
- replace()
- split()
- join()
- find()
- count()
- startswith()
- endswith()

---

# 요약

|기능|예시|
|----|----|
|인덱싱|text[0]|
|슬라이싱|text[1:4]|
|길이|len(text)|
|대문자|upper()|
|소문자|lower()|
|공백 제거|strip()|
|문자 변경|replace()|
|문자 분리|split()|
|문자 합치기|join()|
|문자 찾기|find()|
|문자 개수|count()|
|시작 확인|startswith()|
|끝 확인|endswith()|
|문자열 포매팅|f"{변수}"|
