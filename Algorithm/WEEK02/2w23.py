from collections import deque
import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

snake = deque()
direct = deque()
apple = []

x,y = 1,1
nx_list = [0, 1 ,0, -1]
ny_list = [1, 0, -1, 0]

N = int(input())

N_apple = int(input())
for _ in range(N_apple):
    apple.append(tuple(map(int, input().rstrip().split())))

N_direct = int(input())
for _ in range(N_direct):
    direct.append(list(input().rstrip().split()))

time = 0
i = 0

snake.append((x, y))

while True:

    if direct and time == int(direct[0][0]):
        dirc = direct.popleft()
        if dirc[1] == "D":
            i += 1
        elif dirc[1] == "L":
            i -= 1

    nx = x + nx_list[i % 4]
    ny = x + ny_list[i % 4]
    time += 1

    if (nx, ny) in snake or (nx > N or nx < 1 or ny > N or ny < 1):
        break
    snake.append((nx,ny))
    x=nx
    y=ny

    if (nx,ny) in apple:
        apple.remove((nx,ny))
        continue

    else:
        snake.popleft()

print(time)