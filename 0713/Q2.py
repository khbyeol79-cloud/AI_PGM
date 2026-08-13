import numpy as np
import pandas as pd


# 설정값
SUBJECTS = ["국어", "영어", "수학"]
DECIMAL_PLACES = 2


# 점수 데이터
data = np.array([
    [85, 90, 88],
    [70, 80, 75],
    [95, 98, 100],
    [60, 72, 68]
])


# NumPy 데이터를 DataFrame으로 변환
def create_dataframe(data, columns):
    return pd.DataFrame(data, columns=columns)


# 학생별 평균 추가
def add_average(df):
    df["평균"] = df.mean(axis=1).round(DECIMAL_PLACES)
    return df


# 평균이 가장 높은 학생 검색
def find_top_student(df):
    return df.loc[df["평균"].idxmax()]


# 결과 출력
def print_result(df, student):
    print(df.to_string(index=True))

    print("\n평균이 가장 높은 학생")
    print(student.to_string())


# 실행 부분
df = create_dataframe(data, SUBJECTS)

df = add_average(df)

top_student = find_top_student(df)

print_result(df, top_student)