import sys

N = int(input())
n = 0
P = []
while n<N:
    n+=1
    x = int(sys.stdin.readline())
    P.append(x)

P = sorted(P)

for p in P:
    print(p)