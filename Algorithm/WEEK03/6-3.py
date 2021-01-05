import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N, target = map(int, input().split())

dp = [100001 for _ in range(target + 1)]
dp[0] = 0

coin = sorted(list(set(int(input()) for _ in range(N))))

for j in range(1, target+1):
    for i in coin:
        if j-i < 0:
            break
        dp[j] = min(dp[j], dp[j-i] + 1)

if dp[target] == 100001:
    print(-1)
else:    
    print(dp[target])