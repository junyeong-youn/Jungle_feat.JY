import sys
from collections import deque
import copy

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

tab_num, item_num = map(int, input().split())

A = list(map(int, input().split()))
item_list = deque()
for a in A:
    item_list.append(a)

item_list2 = item_list.copy()

def first(item_list):
    global frist_rank
    double_list = [0 for _ in range(item_num+1)]

    for i in item_list:
        double_list[i] += 1

    for i in range(len(double_list)):
        double_list[i] = (double_list[i], double_list.index(double_list[i]))

    double_list.sort()
    double_list.reverse()

    frist_rank = []

    for i in double_list:
        if i[0] > 0:
            frist_rank.append(i[1])
    
    return frist_rank

firstlist = []
firstlist.append(first(item_list))

for i in range(1, item_num):
    item_list.popleft()
    first(item_list)
    firstlist.append(frist_rank)

print(firstlist)

tab = []
cnt = 0

for i in range(item_num):
    tindex = []
    if item_list2[i] in tab:
        continue

    elif len(tab) < tab_num:
        tab.append(item_list2[i])
        continue

    elif len(tab) == tab_num:
        for k in tab:
            if k in firstlist[i]:
                tindex.append(firstlist[i].index(k))
        tabcut = firstlist[i][max(tindex)]
        tab.remove(tabcut)
        tab.append(item_list2[k])
        cnt += 1

print(cnt)