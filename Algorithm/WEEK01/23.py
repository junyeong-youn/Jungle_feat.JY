K=[]
P=[]
# N = int(input())
m=0
while m<1000:
    m+=1
    K.append(m)


for k in K:
    n = 0
    S = []
    while n<k:
        n+=1
        if k%n == 0:
            S.append(n)
    if len(S) == 2:
        P.append(k)

P.remove(2)

N = int(input())
for _ in range(N):
    T = int(input())
    half = T//2
    for x in range(half, 1, -1):
        if (T-x in P) and (x in P):
            print(x, T-x)
            break
