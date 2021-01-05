N = int(input())
X = []
n = 0

for i in range(N):
    x = str(input())
    X.append(x)

Xz = set(X)
X = list(Xz)

X.sort()

while n<20:
    n+=1
    for x in X:
        if len(x) == n:
            print(x)
