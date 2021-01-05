for i in ()from itertools import combinations

A = []
B = []

for _ in range(9):
    A.append(int(input()))

result = list(combinations(A,7))

for a in result:
    if a[0] + a[1] + a[2] + a[3] + a[4] + a[5] + a[6] == 100:
        B.append(a)

C = list(B[0])
C.sort()

for c in C:
    print(c)
