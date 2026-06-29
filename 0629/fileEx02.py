import os # 운영체제 명령어 사용하기위해
# newfile2.py

os.makedirs("C:/doit",exist_ok=True)  # 운영체제 명령어사용 디렉토리 생성
f = open("C:/doit/새파일.txt", 'w') # 해당 디렉토리가 있어야 해당경로에 생성가능

f.close()
