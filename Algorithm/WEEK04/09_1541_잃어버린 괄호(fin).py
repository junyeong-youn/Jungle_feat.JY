import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

num_list = list(map(str, input().strip().split('-')))

for i in range(len(num_list)):
    if '+' in num_list[i]:
        num_list[i] = num_list[i].split('+')
        for x in range(len(num_list[i])):
            num_list[i][x] = int(num_list[i][x])
        num_list[i] = sum(num_list[i])
    else:
        num_list[i] = int(num_list[i])
ans = num_list[0]

for i in range(1, len(num_list), 1):
    ans = ans - num_list[i]

print(ans)