sum=0
hol=0
six=0

for i in range(1,101):
    sum +=i
    if i%2==1: hol+=i
    if i%6==0: six+=i

print(f"1부터 100까지 합 {sum}")
print(f"1부터 100까지 홀수 합 {hol}")
print(f"1부터 100까지 6의 배수합 {six}")

number = int(input("Enter a number: "))
for i in range(1,number+1):
    for j in range(1,i+1): # print("*" *i)  파이썬에서만 가능
        print("*",end="")
    print()
    
  