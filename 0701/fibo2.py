n = int(input("몇 개의 피보나치 수를 출력할까요? "))
if n <= 0:
    print("양수를 입력하세요.")
else:
    a, b = 0, 1
    result = []
    for _ in range(n):
        result.append(str(a))
        a, b = b, a + b
    print(" ".join(result))

