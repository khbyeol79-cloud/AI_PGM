#1. 두개의 정수를 입력받아 사칙연산의 결과를 출력하세요.
a= int(input("Enter first number : "))
b= int(input("Enter second number : "))

print(f"a+b={(a)+(b)}")
print(f"a-b={(a)-(b)}")
print(f"a*b={(a)*(b)}")
print(f"a/b={(a)/(b):.2f}")



#2. 5개의 정수값을 입력받아 리스트에 저장하고 그 리스트의 합,평균, 최소값, 최대값을 출력하세요.

c=[0,0,0,0,0] #리스트 c를 정의하고 5개의 정수값을 입력받아 저장 or c=[]*5
c[0]= int(input("Enter first number : "))
c[1]= int(input("Enter second number : "))
c[2]= int(input("Enter third number : "))
c[3]= int(input("Enter fourth number : "))
c[4]= int(input("Enter fifth number : "))


print(f"합계 : {sum(c)}")
print(f"평균 : {sum(c)/len(c):.2f}")
print(f"최소값 :{min(c)}")
print(f"최대값 :{max(c)}")



#3. 과일명이 있는 리스트를 정의하고 그 리스트의 첫번째와 마지막 문자열을 출력하세요

fruits = ["apple", "banana", "orange"]
fruit= input("fruits : ")
fruits.append(fruit)

print(fruits)
print(f"첫 번째 과일 : {fruits[0]}")
print(f"마지막 과일 : {fruits[-1]}")


