def addmany(*args): # 매개변수앞에 * 붙이면 입력값을 전부 튜플로생성
    # ** 붙이면 딕셔너리자료형으로 생성
    #print(type(args)) 데이터타입확인
   
    result = 0
    for i in args:
        result+=i
    return result

print(addmany(1,2))
print(addmany(1,2,3,4,5))
print(addmany(1,2,3,4,5,6,7,8,9,10))
