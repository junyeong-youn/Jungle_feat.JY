import sys

sys.stdin = open("input.txt", "r")
input = sys.stdin.readline

N = int(input())
alkali = list(map(int, input().split()))
matrix = []
k = 0

for i in alkali:
    for j in alkali:
        if i == j:
            matrix.append(999)
        elif i*j >= 0:
            matrix.append(abs(i)+abs(j))
        else:
            matrix.append(abs(i+j))

while k < len(matrix):
    if matrix[k] == min(matrix):
        ans1 = k//N
        ans2 = k%N
    k+=1

if alkali[ans1] < alkali[ans2]:
    print(alkali[ans1], end = " ")
    print(alkali[ans2])
else:
    print(alkali[ans2], end = " ")
    print(alkali[ans1])
