import sys
from itertools import combinations

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

bag_num, mx_weight = map(int, input().strip().split())
bag_list = []

dp = [[0 for _ in range(mx_weight + 1)] for _ in range(bag_num)]

for i in range(bag_num):
    weight, good = map(int, input().strip().split())
    for j in range(mx_weight + 1):
        if j >= weight:
            dp[i][j] = max(good + dp[i-1][j-weight], dp[i-1][j])
        else:
            dp[i][j] = dp[i-1][j]

print(dp[-1][-1])