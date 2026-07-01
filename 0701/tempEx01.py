def menu():
    print("1.섭씨>화씨")
    print("2.화씨>섭씨")
    print("3.종료")
    selection = int(input("메뉴 선택"))
    return selection

def ctof(c):
    temp=c*9.0/5.0+32
    return temp

def ftoc(f):
    temp=(f-32)*5.0/9.0
    return temp

def inputf():
    f=float(input("화씨온도입력: "))
    return f

def inputc():
    c=float(input("섭씨온도입력: "))
    return c

def main():
    while True:
        index = menu()
        if index == 1:
            t=inputc()
            t2=ctof(t)
            print(f"섭씨온도 {t}도는 화씨온도 {t2}도입니다.")
        elif index == 2:
            t = inputf()
            t2 = ftoc(t)
            print(f"화씨온도 {t}도는 섭씨온도 {t2}도입니다.")
        else :
            break


if __name__ == "__main__":
    main()