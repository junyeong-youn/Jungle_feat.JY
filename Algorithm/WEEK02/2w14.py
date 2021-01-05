import sys

sys.stdin = open("input.txt", "r")

N = int(sys.stdin.readline())
blist = []

for _ in range(N):
    bracket = list(map(str, sys.stdin.readline().rstrip()))

    if bracket[0] == ')':
        print("NO")
    else:
        blist.append('(')
        n=0

        while n<(len(bracket)- 1):
            n+=1
            if len(blist) == 0:
                blist.append(bracket[n])
            else:
                if blist[-1] == '(' and bracket[n] == ')':
                    blist.pop()
                else:
                    blist.append(bracket[n])
        if len(blist) == 0:
            print("YES")
        else:
            print("NO")
        blist = []
