import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

tab_num, item_num = map(int, input().split())

item_list = list(map(int, input().split()))

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

tab = []
cnt = 0

for i in range(item_num):
    tindex = []
    if item_list[i] in tab:
        continue

    if len(tab) < tab_num:
        tab.append(item_list[i])

    elif len(tab) == tab_num:
        for i in tab:
            tindex.append(frist_rank.index(i))
        tabcut = frist_rank[max(tindex)]
        tab.remove(tabcut)
        tab.append(item_list[i])
        cnt += 1

print(cnt)