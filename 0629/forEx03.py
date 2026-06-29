a= int(input("Enter a number: "))

for i in range(1,a):
    print(" "*(a-i),end="")
    print("*"*(2*i-1))

for i in range(a,0,-1):
    print(" "*(a-i),end="")
    print("*"*(2*i-1))


