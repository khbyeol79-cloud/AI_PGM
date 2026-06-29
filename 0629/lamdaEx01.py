def add(a,b): #1,8라인을 10번 라인으로 사용할수있다
    
    """  
    this
    """
#독스트링(함수 설명) 내용 작성

    return a+b 

#add = lamda a,b:a+b 



result = add(5,3)
print(result)

print(add.__doc__) # 독스트링(설명) 내용 확인
print(add.__name__)