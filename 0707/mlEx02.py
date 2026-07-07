from sklearn.datasets import load_iris # 사이킷런에서붓꽃데이터셋로드
import pandas as pd
from sklearn import svm
import plotly.express as px



iris= load_iris()
df = pd.DataFrame(iris.data)
s=svm.SVC(gamma=0.1,C=10)  # svm 분류 모델 SVC 객체 생성하고
s.fit(iris.data,iris.target)  # iris 데이터로 학습

# 101번째와 51번째 샘플을 변형하여 새로운데이터생성
new_d=[[6.4,3.2,6.0,2.5],[7.1,3.1,4.7,1.35]] 

res=s.predict(new_d)
print("새로운 2개 샘플의 부류는", res)

df = px.data.iris()
# petal_length를 제외하여 3차원 공간 구성
fig = px.scatter_3d(df, x='sepal_length', y='sepal_width', z='petal_width', color='species')
fig.show(renderer="browser")



