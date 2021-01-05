import sys

sys.stdin = open("input.txt", "r")

n = int(sys.stdin.readline())

m = 0

def program(a):
    if a[0:4] == 'push':
        A.append(int(a.replace("push ", "")))
    elif a == 'pop':
        if A == []:
            print(-1)
        else:
            print(A.pop())
    elif a == 'size':
        print(len(A))
    elif a == 'empty':
        if A == []:
            print(1)
        else:
            print(0)
    elif a == 'top':
        if A == []:
            print(-1)
        else:
            print(A[-1])
A = []

while m<n:
    m+=1
    x = str(sys.stdin.readline().strip())

    program(x)
