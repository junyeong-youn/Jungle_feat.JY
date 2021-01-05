import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

first_str = list(map(str, input().strip()))
second_str = list(map(str, input().strip()))


first_str.insert(0, 0)
second_str.insert(0, 0)

def LCS(X, Y):
    global t
    m = len(X)
    n = len(Y)
    t = [[0 for _ in range(n)] for _ in range(m)]
    for i in range(1, m, 1):
        for j in range(1, n, 1):
            if X[i] == Y[j]:
                t[i][j] = t[i-1][j-1] + 1
            else:
                t[i][j] = max((t[i-1][j]),(t[i][j-1]))

LCS(first_str, second_str)

print(max(map(max, t)))
