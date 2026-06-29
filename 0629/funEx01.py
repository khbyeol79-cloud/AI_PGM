def add(a,b):
    return a+b 
def subtract(a,b):
    return a-b
def multiply(a,b):
    return a*b
def divide(a,b):
    if b ==0 :
        raise ValueError("cannot divide by zero")
    return a/b


def main():
    print("Select operation:")
    print("1.Add")
    print("2.subtract")
    print("3.multply")
    print("4.divide")
    choice = input("Enter choice(1/2/3/4):")
    num1 = float(input("first num:"))
    num2 = float(input("second num"))
    
    if choice =='1':
        print(num1,"+",num2,"=",add(num1,num2))
    elif choice =='2':
        print(num1,"-",num2,"=",subtract(num1,num2))
    elif choice =='3':
        print(num1,"*",num2,"=",multiply(num1,num2))
    elif choice=='4':
        try:
            result = divide(num1,num2)
            print(num1,"/",num2,"=",result)
        except ValueError as e:
            print(e)
    else:
        print("Invalid input")

main()



