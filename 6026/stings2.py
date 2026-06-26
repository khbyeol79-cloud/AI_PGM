a=3  #변수선언&지정
b=5

print("I eat %d apples." %a) #  %d=정수출력 / 변수a값 대입
print("I eat %d apples and %d oranges." %(a,b)) #변수a,b값 대입
print("I eat %d apples "%(a+b)) #변수a+b값 대입

print("I eat %f apples." %3.141592) # %f=실수출력 / 실수값 대입
print("I eat %0.2f apples." %3.141592) # %0.2f=소수점아래 2자리까지 출력 / 실수값 대입

str1 = "I eat 2 apples."

print(str1)
print("example1 string : %s" %str1) # %s=문자열출력 / 변수str1값 대입


print("I eat {}".format(3)) #format함수 이용하여 3값 대입
print("I eat {0} bananas, {0} apples and {1} oranges.".format(3,5)) 
                                 #format(0,1) {0}에 3, {1}에 5값 대입
print(f"I eat {3} bananas, {3+5} apples and {5} oranges.") #f문자열 포매팅사용시 수식가능
print("I eat {0} bananas, {2} apples and {1} oranges.".format(a,b,a+b))
                                 #format(0,1,2) {0}에 a, {1}에 b값 대입 
print(f"i eat {a} bananas, {a+b} apples and {b} oranges.") #f문자열 포매팅 이용하여 a,b값 대입 



a= int(input("Enter firest number : ")) #input함수 이용하여 사용자 입력값 a에 대입
# input함수는 문자열로 입력받기 때문에 int함수를 이용하여 정수형으로 변환

b= input("Enter second number : ") #input함수 이용하여 사용자 입력값 b에 대입
print(f"You entered {a} and {b}.") #f문자열 포매팅 이용하여 a,b값 출력
print(f"a+b={(a)+int(b)}")  
print(f"a-b={(a)-int(b)}")  # 앞에 변수a의경우 input함수에 int로 선언하여 int생략 가능
print(f"a*b={(a)*int(b)}") 
print(f"a/b={(a)/int(b):.2f}")  #소수점아래 2자리까지 출력







