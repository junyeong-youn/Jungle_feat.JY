import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

coin_num, target = map(int, input().split())
coin_list = []

for _ in range(coin_num):
    coin_list.append(int(input()))

cnt = 0

while True:
    if target == 0:
        print(cnt)
        exit()

    cnt +=1

    for i in range(len(coin_list)-1):
        if coin_list[i] == target:
            target = 0
            break
        if coin_list[i] < target < coin_list[i+1]:
            target = target - coin_list[i]
            break
