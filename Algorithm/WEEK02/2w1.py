import sys

sys.stdin = open("input.txt", "r")

N = int(sys.stdin.readline())
X = list(map(int, sys.stdin.readline().split()))
M = int(sys.stdin.readline())
Y = list(map(int, sys.stdin.readline().split()))


answer = []
lastanswer = []
tmp = []
k = 0

for y in Y:
    for x in X:
        if x==y:
            tmp.append(1)
        else:
            tmp.append(0)
    answer.append(tmp)
    tmp = []

for i in range(len(answer)):
    for j in range(len(answer[i])):
        k = k + answer[i][j]
    lastanswer.append(k)
    k=0

for a in lastanswer:
    print(a)