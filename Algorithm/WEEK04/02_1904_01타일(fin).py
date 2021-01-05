import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

dp = [0]*1000003

dp[0] = 0
dp[1] = 1
dp[2] = 2

for i in range(3, 1000003, 1):
    dp[i] = ((dp[i-1]) + (dp[i-2])) % 15746

print(dp[int(input())])