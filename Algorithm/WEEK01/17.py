T = int(input())
n=0
while n<T:
    n+=1
    r, S = input().split()
    R = int(r)
    K = list(S)
    m = 0
    L = []
    P = ""
    while m < R:
        L.append(K[m] * R)
        m += 1
        print(L)
    for l in L:
        P = P + l
        print(P)