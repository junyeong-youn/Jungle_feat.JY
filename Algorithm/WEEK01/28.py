import sys

def nqueens(i, col):
    global x
    n = len(col) -1
    if(promising(i, col)):
        if (i == n):
            x = x +1
        else:
            for j in range(1, n+1):
                col[i+1] = j
                nqueens(i+1, col)

def promising(i, col):
    k=1
    flag=True
    while(k<i and flag):
        if (col[i] == col[k] or abs(col[i]-col[k]) == (i-k)):
            flag = False
        k+=1
    return flag

n = int(sys.stdin.readline())

X = []

col = [0] * (n + 1)

x=0

nqueens(0, col)
print(x)
