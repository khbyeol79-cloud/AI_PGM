import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import tensorflow as tf
import numpy as np

ADD_VALUE = 10

# NumPy 배열 생성
numpy_array = np.array([
    [2, 4, 6],
    [8, 10, 12],
    [14, 16, 18]
], dtype=np.float32)

# Tensor 변환
tensor = tf.convert_to_tensor(
    numpy_array,
    dtype=tf.float32
)

print("Tensor:")
print(tensor)

print("\nShape:")
print(tensor.shape)

print("\nDtype:")
print(tensor.dtype)

result = tensor + ADD_VALUE

print("\nTensor + 10:")
print(result)