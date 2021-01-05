import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

coin_num, target = map(int, input().split())
coin_list = [0]
cnt = []

for _ in range(coin_num):
    coin_list.append(int(input()))

def coin():
    global target

    dp = [1000001 for _ in range(coin_num + 1)]

    for i in range(1, coin_num, 1):
        if target//coin_list[i] != 0:
            dp[i] = target//coin_list[i]
        else:
            dp[i] = 1000001

    target = target - coin_list[dp.index(min(dp))] * min(dp)
    cnt.append(min(dp))

    return target

while True:
    if target == 0:
        print(sum(cnt))
        exit()
    coin()