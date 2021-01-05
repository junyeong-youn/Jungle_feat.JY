import sys
from collections import deque

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N, M = map(int, input().split())

glacier = [list(map(int, input().strip().split())) for _ in range(N)]

for i in glacier:
    if not 0 in i:
        print(0)
        exit()

sea = deque()

for x in range(N):
    for y in range(M):
        if glacier[x][y] == 0:
            sea.append((x,y))


scnt = 0
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

def bfs(x, y, cnt):
    q = deque()
    q.append((x, y))
    group[x][y] = cnt
    while q:
        x, y = q.popleft()
        
        # 위 아래 왼쪽 오른쪽 탐색
        for k in range(4):
            nx, ny = x+dx[k], y+dy[k]
            # 지도 밖으로 안 나갔는지 확인
            if 0<=nx<N and 0<=ny<M :
                # 집이 있고, 아직 방문한 곳이 아니라면 꼬우
                if glacier[nx][ny] >= 1 and group[nx][ny] == 0:
                    q.append((nx, ny))
                    group[nx][ny] = cnt
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

while sea:

    visited = [[False for _ in range(M)] for _ in range(N)]

    sea.clear()

    for x in range(N):
        for y in range(M):
            if glacier[x][y] == 0:
                sea.append((x,y))
            if glacier[x][y] > 50:
                glacier[x][y] = 0
                sea.append((x,y))


#!#!##!#!#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    group = [[0]*M for _ in range(N)]
    cnt = 0
    for i in range(N):
        for j in range(M):
            if glacier[i][j] >= 1 and group[i][j] == 0:
                cnt += 1
                bfs(i, j, cnt)
    if cnt >= 2:
        print(scnt)
        exit()
    if cnt == 0:
        print(0)
        exit()

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    nsea = len(sea)
    scnt += 1

    for _ in range(nsea):
        x, y = sea.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0 <= nx < N and 0 <= ny < M:
                if not visited[nx][ny]:
                    if glacier[nx][ny] == 0:
                        continue
                    if glacier[nx][ny] == 1:
                        glacier[nx][ny] = 99
                    glacier[nx][ny] = glacier[nx][ny] -1
    sea.append(1)
                        
                            