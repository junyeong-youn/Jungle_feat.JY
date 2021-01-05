import sys
from collections import deque

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

coin_num, target = map(int, input().strip().split())
coin_list = set([])
queue = deque()
queue.append(0)
cnt = 0
check = [0 for _ in range(target+1)]
for _ in range(coin_num):
    coin_list.add(int(input()))


while queue:

    lenq = len(queue)
    cnt += 1

    for _ in range(lenq):
        coin_sum = queue.popleft()
        if coin_sum == target:
            print(cnt-1)
            exit()
        for i in coin_list:
            if coin_sum <= i:
                coins = coin_sum + i
            if coins <= target and check[coins] == 0:
                check[coins] = 1
                queue.append(coins)