N = int(input())
n = 0
P = []
while n<N:
    n+=1
    x = int(input())
    P.append(x)
    P.sort()

for p in P:
    print(p)