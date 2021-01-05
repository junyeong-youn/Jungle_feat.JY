import sys
from collections import deque
# sys.stdin = open('2667.txt','r')

n = int(input())
board = list(list(map(int, input())) for _ in range(n))

queue = deque()

dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]

def bfs():
    cnt = 1
    while queue :
        y, x = queue.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0 <= ny < n and 0 <= nx < n :
                if board[ny][nx] == 1 :
                    board[ny][nx] = 2
                    queue.append((ny, nx))
                    cnt += 1
    return cnt

result = list()

for i in range(n):
    for j in range(n):
        if board[i][j] == 1 :
            queue.append((i, j))
            board[i][j] = 2
            result.append(bfs())

result = sorted(result)
print(len(result))
print(*result, sep = '\n')
