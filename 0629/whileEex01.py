treeHit = 0
while treeHit < 10:  # while 조건식:
    treeHit += 1
    if treeHit % 2 == 0 : continue # continue 아래실행x / while조건문으로 이동
    print(f"나무를 {treeHit}번 찍었습니다")
    if treeHit ==8 : break # break = while 문 빠져나오기
    if treeHit ==10:
        print("나무 넘어갑니다")


