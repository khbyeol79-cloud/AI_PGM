def abc(a,b):  # a,b 두개로 지정했으면
    return a+b

print(abc(5,3)) # 동일하게 두개를 줘야된다
# a=5 , b=3

def abc2(*a): # *을 붙일경우 
    hap = 0
    for i in a:
        hap+=i
    return hap
print(abc2(1,2,3,4,5)) # 개수제한없이 줄수있다 / 튜플로 지정
# a = (1,2,3,4,5) 튜플

def abc3(**kwargs): # **을 붙일경우 딕셔너리로 지정하여 줄수있다
    for k,v in kwargs.items():
        print(k,v)

abc3(name="alice",age=30,city="new york")

