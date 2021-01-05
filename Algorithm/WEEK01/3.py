A = int(input())
B = list(str(int(input())))
C = []

for b in B:
    b = int(b)
    C.append(b)

q = A * C[2]
w = A * C[1]
e = A * C[0]

sum = q + w*10 + e*100

print(q)
print(w)
print(e)
print(sum)
