# Python 데이터 분석 및 머신러닝 라이브러리 정리

---

# 1. pandas

## pandas란?

pandas는 **데이터 분석과 처리**를 위한 대표적인 라이브러리입니다.

엑셀처럼 행(Row)과 열(Column) 형태의 데이터를 쉽게 다룰 수 있습니다.

```python
import pandas as pd
```

---

## 주요 자료구조

### Series (1차원)

```python
import pandas as pd

s = pd.Series([10,20,30])

print(s)
```

---

### DataFrame (2차원)

```python
import pandas as pd

df = pd.DataFrame({
    "이름":["Kim","Lee","Park"],
    "나이":[20,21,22]
})

print(df)
```

---

## 자주 사용하는 함수

### 데이터 읽기

```python
pd.read_csv("data.csv")
```

### 데이터 저장

```python
df.to_csv("result.csv")
```

### 처음 5개 출력

```python
df.head()
```

### 마지막 5개 출력

```python
df.tail()
```

### 데이터 정보

```python
df.info()
```

### 통계 정보

```python
df.describe()
```

### 열 선택

```python
df["나이"]
```

---

## pandas 사용하는 이유

- 데이터 분석
- 엑셀 처리
- CSV 파일 관리
- AI 데이터 전처리

---

# 2. NumPy (복습)

NumPy는 **배열(Array)과 수치 계산**을 위한 라이브러리입니다.

```python
import numpy as np
```

예제

```python
a = np.array([1,2,3])

print(a*2)
```

출력

```
[2 4 6]
```

---

# 3. scikit-learn (sklearn)

## sklearn이란?

머신러닝(Machine Learning)을 위한 대표적인 라이브러리입니다.

```python
from sklearn import datasets
```

---

## 할 수 있는 일

- 분류(Classification)
- 회귀(Regression)
- 군집화(Clustering)
- 데이터 전처리
- 모델 평가

---

## 주요 모듈

|모듈|기능|
|----|----|
|datasets|예제 데이터|
|linear_model|선형회귀|
|tree|의사결정트리|
|svm|SVM|
|neighbors|KNN|
|metrics|평가|

---

# 4. load_iris()

## load_iris란?

sklearn에서 제공하는 **붓꽃(Iris) 데이터셋**입니다.

머신러닝 입문에서 가장 많이 사용하는 데이터입니다.

```python
from sklearn.datasets import load_iris

iris = load_iris()
```

---

## 데이터 구성

```python
iris.data
```

꽃의 특징

- 꽃받침 길이
- 꽃받침 너비
- 꽃잎 길이
- 꽃잎 너비

---

```python
iris.target
```

꽃 종류

```
0
1
2
```

---

```python
iris.target_names
```

출력

```
['setosa'
 'versicolor'
 'virginica']
```

---

## DataFrame으로 변환

```python
import pandas as pd

df = pd.DataFrame(
    iris.data,
    columns=iris.feature_names
)

print(df.head())
```

---

# 5. linear_model

## linear_model이란?

선형 회귀(Linear Regression)를 위한 모듈입니다.

```python
from sklearn.linear_model import LinearRegression
```

---

## 사용 방법

```python
from sklearn.linear_model import LinearRegression

model = LinearRegression()

model.fit(X,y)
```

---

## 예측

```python
model.predict([[5.0]])
```

---

## 주요 함수

### fit()

학습

```python
model.fit(X,y)
```

---

### predict()

예측

```python
model.predict(X)
```

---

### score()

정확도(R²)

```python
model.score(X,y)
```

---

# 6. matplotlib.pyplot

## matplotlib란?

데이터를 **그래프로 표현**하는 라이브러리입니다.

```python
import matplotlib.pyplot as plt
```

---

## 선 그래프

```python
x=[1,2,3]
y=[2,4,6]

plt.plot(x,y)
plt.show()
```

---

## 산점도

```python
plt.scatter(x,y)
plt.show()
```

---

## 막대그래프

```python
plt.bar(x,y)
plt.show()
```

---

## 히스토그램

```python
plt.hist(y)
plt.show()
```

---

## 제목

```python
plt.title("Graph")
```

---

## X축

```python
plt.xlabel("X")
```

---

## Y축

```python
plt.ylabel("Y")
```

---

## 자주 사용하는 함수

- plot()
- scatter()
- bar()
- hist()
- show()
- title()
- xlabel()
- ylabel()

---

# 7. plotly.express

## plotly.express란?

인터랙티브(확대, 축소, 마우스 오버 가능) 그래프를 만드는 라이브러리입니다.

```python
import plotly.express as px
```

---

## 산점도

```python
fig = px.scatter(df,
                 x="sepal length (cm)",
                 y="petal length (cm)")

fig.show()
```

---

## 선 그래프

```python
fig = px.line(df)

fig.show()
```

---

## 막대그래프

```python
fig = px.bar(df,
             x="species",
             y="petal length (cm)")
```

---

## 히스토그램

```python
fig = px.histogram(df,
                   x="petal length (cm)")
```

---

## 특징

- 확대/축소 가능
- 마우스 정보 표시
- 웹 기반 그래프
- Jupyter Notebook에서 많이 사용

---

# 8. datetime

## datetime이란?

날짜와 시간을 다루는 표준 라이브러리입니다.

```python
import datetime
```

---

## 현재 날짜

```python
today = datetime.date.today()

print(today)
```

---

## 현재 시간

```python
now = datetime.datetime.now()

print(now)
```

---

## 년/월/일

```python
print(now.year)
print(now.month)
print(now.day)
```

---

## 시/분/초

```python
print(now.hour)
print(now.minute)
print(now.second)
```

---

## 날짜 지정

```python
d = datetime.date(2025,7,10)
```

---

## 날짜 계산

```python
from datetime import timedelta

today = datetime.date.today()

tomorrow = today + timedelta(days=1)

print(tomorrow)
```

---

## 날짜 형식 변경

```python
now.strftime("%Y-%m-%d")
```

출력

```
2025-07-10
```

---

# 라이브러리 관계

```
NumPy
   │
   ├── 배열(Array)
   │
   ▼
pandas
   │
   ├── 데이터 처리(DataFrame)
   │
   ▼
scikit-learn
   │
   ├── 머신러닝
   │
   ▼
matplotlib / plotly
   │
   ├── 그래프 시각화
```

---

# 한눈에 정리

## pandas

```
데이터 분석

Series
DataFrame
CSV
```

---

## NumPy

```
배열(Array)

행렬 연산

수치 계산
```

---

## sklearn

```
머신러닝

분류
회귀
예측
```

---

## load_iris

```
붓꽃 데이터

150개 데이터

3가지 품종
```

---

## linear_model

```
선형회귀

fit()

predict()

score()
```

---

## matplotlib

```
기본 그래프

plot()

scatter()

bar()
```

---

## plotly.express

```
인터랙티브 그래프

확대

축소

마우스 정보
```

---

## datetime

```
현재 날짜

현재 시간

날짜 계산

시간 계산
```

---

# 요약

|라이브러리|용도|
|---------|------------------------------|
|NumPy|배열 및 수치 계산|
|pandas|데이터 분석 및 전처리|
|scikit-learn(sklearn)|머신러닝 모델 학습 및 예측|
|load_iris|머신러닝 연습용 붓꽃 데이터셋|
|linear_model|선형 회귀 모델|
|matplotlib.pyplot|기본 데이터 시각화|
|plotly.express|인터랙티브 데이터 시각화|
|datetime|날짜와 시간 처리|

CSV 데이터
     │
     ▼
pandas
(데이터 읽기/정리)
     │
     ▼
NumPy
(배열 변환 및 수치 계산)
     │
     ▼
sklearn
(머신러닝 모델 학습)
     │
     ▼
linear_model
(선형회귀 예측)
     │
     ▼
matplotlib / plotly.express
(결과 시각화)
     │
     ▼
datetime
(학습 시간, 로그, 날짜 관리)
