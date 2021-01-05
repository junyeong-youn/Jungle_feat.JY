import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

coin_num, target = map(int, input().split())
coin_list = [0]
cnt = 0

for _ in range(coin_num):
    coin_list.append(int(input()))

while True:

    if target == 0:
        print(cnt)
        exit()

    twobreak = False

    for i in range(1, coin_num+1, 1):
        if coin_list[-i] <= target:
            cnt += 1
            target -= coin_list[-i]
            twobreak = True
            break
    if twobreak == True:
        continue

