
money = int(input("현재 금액 "))

if money >= 20000:  
    print("택시를 ") # if문 내용은 들여쓰기
    print("타고가라") # 들여쓰기는 같은깊이로 맞춰야함
else:  # if문은 : 을 입력해야함
    print("걸어가라")
print("Good night") # 들여쓰기를 안하면 if문과 상관없이 출력됨



ent = 10000
age = int(input("나이 : "))

if age >= 20:
    ent = ent + ent * 0.1

print(f"입장료 = {ent}")


