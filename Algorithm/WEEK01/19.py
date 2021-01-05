A, B = map(int, input().split())

a=list(str(A))
b=list(str(B))

a.reverse()
b.reverse()

am = list(map(int,a))
bm = list(map(int,b))

An = am[0] * 100 + am[1] * 10 + am[2]
Bn = bm[0] * 100 + bm[1] * 10 + bm[2]

if An>Bn:
    print(An)
else:
    print(Bn)

