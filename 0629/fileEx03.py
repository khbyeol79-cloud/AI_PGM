# write_data.py

f = open("C:/doit/새파일.txt", 'w') # w = 생성 및 내용쓰기
for i in range(1, 11):
    data = f"{i}번째 줄입니다.\n"
    f.write(data)
f.close()

# add_data.py
f = open("C:/doit/새파일.txt",'a') # a = 내용추가
for i in range(11, 20):
    data = f"{i}번째 줄입니다.\n"
    f.write(data)
f.close()
