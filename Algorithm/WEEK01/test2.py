n = int(input())
X=[]
X.append(1)
X.append(2)
X.append(4)
print(X)
for _ in range(n):
    x = int(input())
    for i in range(x):
        if i == 0 or i == 1 or i == 2:
            continue
        else:
            X.append(X[i-1] + X[i-2] + X[i-3])
            print(X)
        print(X[x])