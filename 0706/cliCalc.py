while True:
    print("\n=== 계산기 ===")
    print("1. 더하기")
    print("2. 빼기")
    print("3. 곱하기")
    print("4. 나누기")
    print("0. 종료")

    choice = input("메뉴 선택: ")

    if choice == "0":
        print("프로그램을 종료합니다.")
        break

    if choice not in ("1", "2", "3", "4"):
        print("잘못된 입력입니다.")
        continue

    num1 = float(input("첫 번째 숫자: "))
    num2 = float(input("두 번째 숫자: "))

    if choice == "1":
        print(f"결과: {num1 + num2}")
    elif choice == "2":
        print(f"결과: {num1 - num2}")
    elif choice == "3":
        print(f"결과: {num1 * num2}")
    elif choice == "4":
        if num2 == 0:
            print("0으로 나눌 수 없습니다.")
        else:
            print(f"결과: {num1 / num2}")

            