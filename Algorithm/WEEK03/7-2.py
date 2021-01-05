import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

dx = [0, 0, -1, 1]
dy = [-1, 1, 0, 0]

R,C = list(map(int, input().strip().split()))

graph = [list(map(str, input().strip())) for _ in range(R)]

visited = [[False for _ in range(C)] for _ in range(R)]

stack = [(0, 0)]

alpha = []
alpha.append(graph[0][0])

tracking = []
cnt = 0

while stack:
    
    x, y = stack.pop()
    if visited[x][y]:
        cnt -= 1 
        continue
    tracking = tracking + [[x, y]]
    print(x, y, tracking)
    alpha.append(graph[x][y])
    
    visited[x][y] = True
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        if nx < 0 or ny < 0 or nx >=R or ny >= C:
            continue
        if graph[nx][ny] in alpha:
            continue
        if graph[nx][ny] not in alpha:
            stack.append((nx, ny))
            cnt += 1
        else:
            cnt -= 1
            
if cnt == 0:
    print(1)
else:
    print(cnt)