import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

dx = [0, 0, -1, 1]
dy = [-1, 1, 0, 0]

R,C = list(map(int, input().strip().split()))

graph = [list(map(str, input().strip())) for _ in range(R)]

visited = [[False for _ in range(C)] for _ in range(R)]

stack = []

x=0
y=0

while x < R:
    y=0
    while y < C:
        stack.append((x, y))
        y+=1
    x+=1

alpha = [graph[0][0]]
graph[0][0] = 1
x, y = 0, 0

while stack:

    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        
        if nx >= R or nx < 0 or ny >= C or ny < 0:
            continue
        if (nx, ny) not in stack:
            continue
        if isinstance(graph[nx][ny], int) == True:
            continue
        if graph[nx][ny] not in alpha:
            alpha.append(graph[nx][ny])
            graph[nx][ny] = graph[x][y] + 1
            stack.remove((nx, ny))
            x = nx
            y = ny
        else:
            print(graph[x][y])
            exit()
            max()