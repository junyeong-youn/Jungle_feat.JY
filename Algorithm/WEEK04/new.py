import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

bag_num, mx_weight = map(int, input().strip().split())

dp = [[0 for _ in range(mx_weight + 1)] for _ in range(bag_num)]

for i in range(bag_num):
    weight, value = map(int, input().split())
    for j in range(1,mx_weight+1):
        if j >= weight:
            dp[i][j] = max(value + dp[i-1][j-weight], dp[i-1][j])
        else:
            dp[i][j] = dp[i-1][j]

print(max(map(max, dp)))
print(dp)