import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

dp = [0] * 100

def fibo(x):
    if x == 1 or x == 2:
        return 1
    if dp[x] != 0:
        return dp[x]
    dp[x] = fibo(x-1) + fibo(x-2)
    return dp[x]

print(fibo(int(input())))