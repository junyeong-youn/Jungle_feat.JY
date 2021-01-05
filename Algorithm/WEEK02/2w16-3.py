import sys

sys.stdin = open("input.txt" , "r")

input = sys.stdin.readline

N = int(input())

high = list(map(int, input().split()))
X = []
count = 0
start = 0
m = 0

while m<N-1:
    m+=1
    start = high[-m]
    for i in range(m+1, N+1):
        target = high[-i]
        if i == N and i != N:
            X.append(0)
        elif target > start:
            X.append(-i%N+1)
            break
            X.append(0)
X.append(0)

X.reverse()

print(*X, sep= ' ')