score = int(input("점수 입력:"))
onedigit = score // 10

result = "합격" if score >= 60 else "불합격" # 조건부 표현식(가독성떨어짐)

match score: #수식
    case score if score >= 90:  #조건
        print("우수")
    case score if score >= 80:
        print("보통")
    case score if score >= 70:
        print("노력 필요")
    case score if score >= 60:
        print("재시험 필요")
    case _:  
        print("점수향상필요") 

match onedigit: #수식
    case 10|9: # 값
        print("우수")
    case 8:
        print("보통")
    case 7:
        print("노력 필요")
    case 6:
        print("재시험 필요")
    case _:
        print("점수향상필요")
