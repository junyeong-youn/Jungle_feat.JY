A = []
n = 0
m = 0
while n<9:
    n+=1
    a = int(input())
    A.append(a)

Max = max(A)
print(Max)

for a in A:
    m+=1
    if a == Max:
        print(m)

