import sys
from collections import deque

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

coin_num, target = map(int, input().strip().split())
coin_list = set([])
queue = deque()
queue.append(target)
cnt = 0
for _ in range(coin_num):
    coin_list.add(int(input()))


while queue:

    lenq = len(queue)
    cnt += 1

    for _ in range(lenq):
        remainder = queue.popleft()
        if remainder == 0:
            print(cnt-1)
            exit()
        for i in coin_list:
            remain = remainder - i
            if remain >= 0:
                queue.append(remain)
