import sys

sys.stdin = open("JY/input.txt", "r")

dp = [0] * 93

dp[0] = 0
dp[1] = 1
dp[2] = 1

for i in range(3, 93, 1):
    dp[i] = dp[i-2] + dp[i-1]

print(dp[int(input())])
