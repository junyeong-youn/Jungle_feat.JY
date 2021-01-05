import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N, M = map(int, input().split())

c_list = [list(map(str, input().strip())) for _ in range(N)]
stack = []
alpha = list(range(65, 92,1))

for x in range(N):
    for y in range(M):
        c_list[x][y] = ord(c_list[x][y])

dx = [0, 0, -1, 1]
dy = [-1, 1, 0, 0]

stack.append((0, 0))
c_list[0][0] = 100

while stack:
    
    x, y = stack.pop()

    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        if 0 <= nx < N and 0 <= ny < M:
            if c_list[nx][ny] in alpha:
                alpha.remove(c_list[nx][ny])
                c_list[nx][ny] = c_list[x][y] + 1
                stack.append((nx, ny))
    
    
print(max(map(max, c_list)) - 99)
