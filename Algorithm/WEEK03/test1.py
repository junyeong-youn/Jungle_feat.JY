import sys
from collections import deque

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N = int(input())
apt = [list(map(int, input().rstrip())) for _ in range(N)]

def bfs(x, y, cnt):
    q = deque()
    q.append((x, y))
    group[x][y] = cnt
    while q:
        x, y = q.popleft()
        
        
        for i in range(4):
            nx, ny = x+dx[i], y+dy[i]
            
            if 0<=nx<N and 0<=ny<N :
                if apt[nx][ny] == 1 and group[nx][ny] == 0:
                    q.append((nx, ny))
                    group[nx][ny] = cnt


dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

group = [[0]*N for _ in range(N)]

cnt = 0

ncntlist = []

for i in range(N):
    for j in range(N):
        if apt[i][j] == 1 and group[i][j] == 0:
            cnt += 1
            bfs(i, j, cnt)

print(cnt)
for i in range(1, cnt+1):
    ncnt = 0
    for x in range(N):
        for y in range(N):
            if group[x][y] == i:
                ncnt += 1
    ncntlist.append(ncnt)

ncntlist.sort()

for i in ncntlist:
    print(i)