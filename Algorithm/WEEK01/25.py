x, y = map(int, input().split())
N = int(input())
X=[]
Y=[]
PX=[]
PY=[]
n=0

while n<N:
    n+=1
    J, P = map(int, input().split())
    if J == 0:
        PY.append(P)
    elif J == 1:
        PX.append(P)

PX.append(x)
PY.append(y)
PX.append(0)
PY.append(0)
PX.sort()
PY.sort()
PX.reverse()
PY.reverse()

fx=0
fy=0

m=0
l=0

while m<len(PX)-1:
    m+=1
    X.append(PX[m-1]-PX[m])


while l<len(PY)-1:
    l+=1
    Y.append(PY[l-1]-PY[l])

print(max(X) * max(Y))