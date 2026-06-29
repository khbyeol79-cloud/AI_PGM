score = int(input("점수 입력:"))

if score >= 90:
    print("우수")
elif score >= 80:
    print("보통")
elif score >= 70:
    print("노력 필요")
elif score >= 60:
    print("재시험 필요")
else:
    print("불합격")

print("프로그램 종료")
