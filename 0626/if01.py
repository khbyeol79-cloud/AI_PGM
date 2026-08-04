score = int(input("점수를 입력하세요: "))
if score >= 90:
    print("A학점입니다.")
elif score >= 80:
    print("B학점입니다.")
elif score >= 70:
    print("C학점입니다.")
elif score >= 60:
    print("D학점입니다.")
else:
    print("F학점입니다.")


year = int(input("연도를 입력하세요: "))

if year%4 ==0 and year%100 !=0 or year%400 ==0:
    print(f"{year}년은 윤년입니다.")
else:
    print(f"{year}년은 평년입니다.")


