import sys
from collections import deque

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

coin_num, target = map(int, input().strip().split())
coin_list = []
queue = deque()
A = []
tracking = []

for _ in range(coin_num):
    coin_list.append(int(input()))

coin_list.reverse
for i in coin_list:
    queue.append(i)

n=0
cnt = 0
# (target//min(coin_list)):
while cnt < 5:
    k = len(queue)
    while n<k:
        v = queue.popleft()
        tracking = tracking + [v]
        A.append(v)
        print(tracking)
        if sum(tracking) == target:
            print(len(tracking))
            exit()
        
        for i in coin_list:
            queue.append(i)
            A.append(i)
            
        n+=1
    
    cnt += 1
    A.append(cnt)