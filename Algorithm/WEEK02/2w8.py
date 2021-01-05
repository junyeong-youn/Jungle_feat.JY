import sys

sys.stdin = open("input.txt", "r")

A, B, C = list(map(int, sys.stdin.readline().split()))

AB  = []
n=0

while n<B:
    n+=1
    AB.append(A)

while True:
    if len(AB) == 1:
        if AB[0] > C:
            AB[0] = AB[0] % C
        break
    else:
        if AB[0] >= C:
            AB[0] = AB[0]%C
        else:
            AB.pop()
            AB[0] = AB[0]*A

print(AB[0])