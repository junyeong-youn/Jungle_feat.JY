# from collections import deque
import sys

sys.stdin = open("input.txt", "r")
input  = sys.stdin.readline

N, M = list(map(int, input().split()))

dmap = [list(map(str, input().strip())) for _ in range(N)]

n=0
m=0
k=0
water_point = []

while n < N:
    m=0
    while m < M:
        if dmap[n][m] == '.':
            dmap[n][m] = 0
        if dmap[n][m] == 'D':
            dp = (n,m)
            dmap[n][m] = -10
        if dmap[n][m] == 'X':
            dmap[n][m] = -2
        if dmap[n][m] == 'S':
            st = (n,m)
            dmap[n][m] = 1
        if dmap[n][m] == '*':
            dmap[n][m] = -1
            water_point.append((n, m))
        m+=1
    n+=1

dx = [0, 0, -1, 1]
dy = [-1, 1, 0, 0]
dwx = [0, 0, -1, 1]
dwy = [-1, 1, 0, 0]

visited = [[False]*M for _ in range(N)]
wvisited = [[False]*M for _ in range(N)]

print(dmap)

def bfs():
    global k
    person = set()
    water = set()

    person.add(st)
    for i in water_point:
        water.add(i)

    while person:

        x, y = person.pop()
        visited[x][y]

        waterp = len(water)
        k=0
    
        while k < waterp:
            wx, wy = water.pop()
            visited[wx][wy]

            for i in range(4):
                nwx = wx + dwx[i]
                nwy = wy + dwy[i]
                if nwx < 0 or  nwy < 0 or  N <= nwx or M <= nwy:
                    continue
                if visited[nwx][nwy]:
                    continue
                if dmap[nwx][nwy] == -2:
                    continue
                if dmap[nwx][nwy] == -10:
                    continue
                if dmap[nwx][nwy] == max(map(max, dmap)):
                    if max(map(max, dmap)) > 0:
                        cnt = 0
                        for a in dmap:
                            for b in a:
                                if b == max(map(max, dmap)):
                                    cnt = cnt +1
                        if cnt == 1:
                            print("KAKTUS")
                            exit()
                  
                else:
                    dmap[nwx][nwy] = -1
                    water.add((nwx, nwy))
            k+=1       

        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if nx < 0 or  ny < 0 or  N <= nx or M <= ny:
                continue
            if visited[nx][ny]:
                continue
            if dmap[nx][ny] == -1:
                continue
            if dmap[nx][ny] == -2:
                continue
            if dmap[nx][ny] == 0:
                person.add((nx, ny))
                dmap[nx][ny] = dmap[x][y] + 1
            if dmap[nx][ny] == -10:
                dmap[nx][ny] = dmap[x][y] + 1
                print(dmap[nx][ny]-1)
                exit()
        
        
                

bfs()

print(dmap)