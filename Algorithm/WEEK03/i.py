import sys
from collections import deque

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

coin_num, target = map(int, input().strip().split())
coin_list = []
queue = deque()


for _ in range(coin_num):
    coin_list.append(int(input()))

for i in coin_list:
    queue.append(i)

for i in coin_list:
    add(i) = []
for i in range(len(coin_list)):


print(coin_list)
print(1)