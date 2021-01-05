x = input()
X = x.split(" ")
while '' in X:
    X.remove('')
print(len(X))