import sys
from collections import deque

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

tab_num, item_num = map(int, input().split())

item_list = list(map(int, input().split()))

change_item_list = deque()

for i in range(len(item_list)):
    change_item_list.append(item_list[i])
for _ in range(tab_num-2):
    change_item_list.popleft()

tap = []
cnt = 0

for i in range(item_num):
    if i == item_num - 1:
        pass
    else:
        change_item_list.popleft()

    if len(tap) < tab_num:
        tap.append(item_list[i])
        continue
    if item_list[i] in tap:
        continue
    if len(tap) == tab_num:
        dis_list = []
        for x in range(len(tap)):
            if tap[x] in change_item_list:
                dis = change_item_list.index(tap[x])
                dis_list.append(dis)
            else:
                dis = 9999
                dis_list.append(dis)
        a = tap[dis_list.index(max(dis_list))]
        tap.remove(a)
        cnt += 1 
        tap.append(item_list[i])

print(cnt)
