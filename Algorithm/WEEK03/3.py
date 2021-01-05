from collections import deque
import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N, M = list(map(int, input().split()))

graph = [list(map(int, input().rstrip())) for _ in range(N)]

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

def dfs(x, y):

    global N, M

    queue = deque()
    queue.append((x,y))

    while queue:
        x, y = queue.popleft()

        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
        
            if nx < 0 or ny < 0 or N <= nx or M <= ny:
                continue
            
            if graph[nx][ny] == 0:
                continue

            if graph[nx][ny] == 1:
                graph[nx][ny] = graph[x][y] + 1
                queue.append((nx, ny))
            
    return graph[N-1][M-1]

print(dfs(0,0))

print(graph)