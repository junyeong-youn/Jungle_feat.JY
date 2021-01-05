N = int(input())
K = list(map(int, input().split()))

P = []

for k in K:
    n = 0
    S = []
    while n<k:
        n+=1
        if k%n == 0:
            S.append(n)
    if len(S) == 2:
        P.append(k)

print(len(P))

