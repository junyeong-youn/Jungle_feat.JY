A = int(input())
B = int(input())
C = int(input())
n = -1

k = A * B * C
D = list(str(k))
E = []

for x in D:
    E.append(int(x))

while n<9:
    n+=1
    q = E.count(n)
    print(q)