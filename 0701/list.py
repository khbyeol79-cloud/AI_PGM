s= [
   [1,2,3,4,5],
   [6,7,8,9,10],
   [11,12,13,14,15],
   [16,17,18,19,20]
]

print(s)
print(s[1])
print(s[2][4])

for i in range(len(s)):
    for j in range(len(s[i])):
        s[i][j] +=1
    
print(s)

