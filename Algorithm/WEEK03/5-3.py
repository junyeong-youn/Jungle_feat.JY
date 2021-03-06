from collections import deque
import sys

sys.stdin = open("input.txt","r")

input = sys.stdin.readline

amurensis = deque()
water = deque()
tracking = 0
R, C = map(int, input().split())
tmap = [list(map(str, input().rstrip())) for _ in range(R)]
tier = []
for x in range(R):
    for y in range(C):
        if tmap[x][y] == 'S':
            tmap[x][y] = 1
            amurensis.append((x, y))
        if tmap[x][y] == 'D':
            tmap[x][y] = -100
        if tmap[x][y] == '.':
            tmap[x][y] = 0
        if tmap[x][y] == '*':
            tmap[x][y] = -1
            water.append((x, y))
        if tmap[x][y] == 'X':
            tmap[x][y] = -5

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
dwx = [-1, 1, 0, 0]
dwy = [0, 0, -1, 1]

visited_am = [[False for _ in range(C)] for _ in range(R)]
visited_water = [[False for _ in range(C)] for _ in range(R)]

while amurensis:

    len_am = len(amurensis)
    tier.append(len_am)
    
    for _ in range(len_am):

        x, y  = amurensis.popleft()
        tracking = tracking + 1
        visited_am[x][y] = True

        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0 <= nx < R and 0 <= ny < C and not visited_am[nx][ny]:
                if tmap[nx][ny] == -1:
                    continue
                if tmap[nx][ny] == -5:
                    continue
                if tmap[nx][ny] == -100:
                    print(len(tier))
                    exit()
                if tmap[nx][ny] == 0:
                    tmap[nx][ny] = 1
                    tmap[x][y] = 0
                    amurensis.append((nx, ny))

    len_water = len(water)
    
    for _ in range(len_water):
        wx, wy  = water.popleft()
        visited_water[wx][wy] = True
        for i in range(4):
            nwx = wx + dwx[i]
            nwy = wy + dwy[i]
            if 0 <= nwx < R and 0 <= nwy < C and not visited_water[nwx][nwy]:
                if tmap[nwx][nwy] == -5:
                    continue
                if tmap[nwx][nwy] == -100:
                    continue
                if tmap[nwx][nwy] == -1:
                    continue
                if tmap[nwx][nwy] == 0:
                    tmap[nwx][nwy] = -1
                    water.append((nwx, nwy))
                    visited_water[nwx][nwy] = True
                if tmap[nwx][nwy] == 1:
                    cnt = 0
                    for x in range(R):
                        for y in range(C):
                            if tmap[x][y] == 1:
                                cnt += 1
                    if cnt == 1:
                        print("KAKTUS")
                        exit()
                        
                    tmap[nwx][nwy] = -1
                     
print("KAKTUS")