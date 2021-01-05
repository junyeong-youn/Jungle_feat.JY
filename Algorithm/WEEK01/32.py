import sys

N = int(input())

Checklist = [0] * 10001

for i in range(N):
    x = int(sys.stdin.readline())
    Checklist[x] = Checklist[x] + 1

for i in range(10001):
    if Checklist[i] != 0:
        for j in range(Checklist[i]):
            print(i)