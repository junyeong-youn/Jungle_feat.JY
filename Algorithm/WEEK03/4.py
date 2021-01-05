from collections import deque
import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N, M, H = list(map(int, input().split()))

n=0
m=0
h=0

graph = []
for _ in range(H):
    graph.append([list(map(int, input().split())) for _ in range(M)])

goodapple_list = []

dz = [-1, 1, 0, 0, 0, 0]
dx = [0, 0, -1, 1, 0, 0]
dy = [0, 0, 0, 0, -1, 1]


while h<H:
    m=0
    while m<M:
        n=0
        while n<N:
            if graph[h][m][n] == 1:
                goodapple_list.append((h, m, n))
            n+=1
        m+=1
    h+=1    


print(goodapple_list)


def bfs():
    global N, M, H
    queue = deque()
    for i in goodapple_list:
        queue.append(i)
    
    while queue:
        z, x, y = queue.popleft()

        for i in range(6):
            nz = z + dz[i]
            nx = x + dx[i]
            ny = y + dy[i]
            
            if nx < 0 or ny < 0 or nz < 0 or nx >= M or ny >= N or nz >= H:
                continue

            if graph[nz][nx][ny] == -1:
                continue

            if graph[nz][nx][ny] > 0:
                continue

            if graph[nz][nx][ny] == 0:
                graph[nz][nx][ny] = graph[z][x][y] + 1
                queue.append((nz, nx, ny))
    
    
bfs()

print(graph)

threetimebreak = True
twotimebreak = True


max_cnt = 0
for z in graph:
    for x in z:
        for y in x:
            max_cnt = max(max_cnt, y)
            if y == 0:
                print(-1)
                exit()
                

print(max_cnt - 1)