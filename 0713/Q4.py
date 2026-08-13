import os

os.environ["TF_ENABLE_ONEDNN_OPTS"] = "0"

import numpy as np
import tensorflow as tf

# 데이터
x_train = np.array([1,2,3,4,5], dtype=np.float32)
y_train = np.array([3,6,9,12,15], dtype=np.float32)


# 1. 모델 생성 [Dense=완전 연결층(Fully Connected Layer)]
model = tf.keras.Sequential([
    tf.keras.layers.Input(shape=(1,)),
    tf.keras.layers.Dense(1)
])



# 2. 모델 컴파일 [optimizer=학습하면서 가중치와 편향을 수정하는 방법]
model.compile(
    optimizer=tf.keras.optimizers.Adam(),
    loss="mse"
) # mse=예측값과 실제값 차이를 계산




# 3. 모델 학습 [epochs=전체 데이터를 몇번 반복 학습할지]
model.fit(
    x_train,
    y_train,
    epochs=300,
    verbose=0
)


# 4. 테스트 데이터 예측
x_test = np.array([6,7,8], dtype=np.float32)

prediction = model.predict(x_test)


# 결과 출력
for x, y in zip(x_test, prediction):
    print(f"x={x} → 예측 y={y[0]:.2f}")