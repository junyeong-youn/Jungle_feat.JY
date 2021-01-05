from collections import deque
import sys
import copy

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N, M = map(int, input().split())

amap = [list(map(str, input().strip())) for _ in range(N)]

animal = deque()
water = deque()

wmap = copy.deepcopy(amap)

for x in range(N):
    for y in range(M):
        if amap[x][y] == 'D':
            amap[x][y] = -100
            fix_x, fix_y = x, y
        if amap[x][y] == 'S':
            amap[x][y] = 1
            animal.append((x, y))
        if amap[x][y] == '.':
            amap[x][y] = 0
        if amap[x][y] == 'X':
            amap[x][y] = -5
        if amap[x][y] == '*':
            amap[x][y] = -1
            water.append((x, y))

for x in range(N):
    for y in range(M):
        if wmap[x][y] == 'D':
            wmap[x][y] = -100
            fix_x, fix_y = x, y
        if wmap[x][y] == 'S':
            wmap[x][y] = 0
            animal.append((x, y))
        if wmap[x][y] == '.':
            wmap[x][y] = 0
        if wmap[x][y] == 'X':
            wmap[x][y] = -5
        if wmap[x][y] == '*':
            wmap[x][y] = 1
            water.append((x, y)) 

dx = [0, 0, -1, 1]
dy = [-1, 1, 0, 0]

visited = [[False for _ in range(M)] for _ in range(N)]
wa_visited = [[False for _ in range(M)] for _ in range(N)]
dlist = []

acnt = 0
wcnt = 0

while water:

    wcnt += 1
    len_water = len(water)

    for _ in range(len_water):
        x, y = water.popleft()
        wa_visited[x][y] = True
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if nx < 0 or ny < 0  or nx >= N or ny >= M:
                continue
            if wa_visited[nx][ny]:
                continue
            if wmap[nx][ny] == -5:
                continue
            if nx == fix_x and ny == fix_y:
                continue
            if wmap[nx][ny] == 0:
                wmap[nx][ny] = wmap[x][y] + 1
                water.append((nx, ny))

while animal:
    
    acnt += 1 
    len_animal = len(animal)

    for _ in range(len_animal):
        x, y = animal.popleft()
        visited[x][y] = True
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if nx < 0 or ny < 0  or nx >= N or ny >= M:
                continue
            if visited[nx][ny]:
                continue
            if amap[nx][ny] == -5:
                continue
            if amap[nx][ny] == -1:
                continue
            if amap[nx][ny] == 0:
                if wmap[nx][ny] == 0:
                    amap[nx][ny] = amap[x][y] + 1
                    animal.append((nx, ny))
                elif acnt + 1 < wmap[nx][ny]:
                    amap[nx][ny] = amap[x][y] + 1
                    animal.append((nx, ny))
            if amap[nx][ny] == -100:
                print(amap[x][y])
                exit()

print("KAKTUS")
