import sys

sys.stdin = open("input.txt", "r")

num = int(sys.stdin.readline())
matrix = []
blue = 0
white = 0

for _ in range(num):
    line = list(map(int, sys.stdin.readline().split()))
    matrix.append(line)

def cut(x, y, n):
    global blue, white
    check = matrix[x][y]
    for i in range(x, x+n):
        for j in range(y, y+n):
            if check != matrix[i][j]:
                cut(x, y, n//2)
                cut(x, y+n//2, n//2)
                cut(x+n//2, y, n//2)
                cut(x+n//2, y+n//2, n//2)
                return
    if check == 0:
        white += 1
    else:
        blue += 1

cut(0,0,num)

print(white)
print(blue)