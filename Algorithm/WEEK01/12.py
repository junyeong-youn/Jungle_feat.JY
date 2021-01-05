def Onumeber(x):
    n = 0
    m = 0
    while n < x:
        n += 1
        m = m + n
    return m

def count(I):
    K=[]
    for i in I:
        K.append(len(i))
    return K

X = int(input())
n=0

while n<X:
    n+=1
    A = str(input())
    B = A.split("X")
    C = count(B)
    D = []
    for c in C:
        D.append(Onumeber(c))
        SUM = 0
        for d in D:
            SUM = SUM + d
    print(SUM)