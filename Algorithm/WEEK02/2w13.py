import sys

sys.stdin = open("input.txt","r")

N = int(sys.stdin.readline())

A = []
max = 0
n = 0

while n < N:
    n+=1
    num = int(sys.stdin.readline())
    if num == 0:
        A.pop()
    else:
        A.append(num)

for a in A:
    max = max + a

print(max)