import sys
from collections import deque

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

start, target = map(int, input().strip().split())

if start == target:
    print(0)
    exit()

queue = deque()
queue.append(start)
cnt = 0

visited = [False for _ in range(200001)]


while queue:

    lenq = len(queue)
    cnt += 1

    for _ in range(lenq):
        remainder = queue.popleft()
        if not visited[remainder]:
            visited[remainder] = True
            if remainder == target:
                print(cnt-1)
                exit()

            remain = remainder + 1
            if 0 <= remain < 200000:
                queue.append(remain)
            
            remain = remainder - 1
            if 0 <= remain < 200000:
                queue.append(remain)

            remain = remainder * 2
            if 0 <= remain < 200000:
                queue.append(remain)