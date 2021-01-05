X = list(map(int, input().split()))
A = X[0]
B = X[1]
V = X[2]
n = (V-B)/(A-B)

if n%1 == 0:
    n=n
else:
    n=n+1
print(int(n))