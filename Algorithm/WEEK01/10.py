N, X = map(int, input().split())
A = list(map(int, input().split()))
B = []
for a in A:
    if a<X:
        B.append(a)
n=0
for b in B:
    print(B[n], end=' ')
    n+=1