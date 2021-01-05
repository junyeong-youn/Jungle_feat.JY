import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

dp = [0 for _ in range(12)]

first_str = list(map(str, input().rstrip()))
second_str = list(map(str, input().rstrip()))

for i in range(len(first_str)):
    if first_str[i] == second_str[0]:
        if dp[i] == 0:
            k = i
            break
            
for i in range(k, len(first_str), 1):
    dp[i] = dp[i] + 1

print(dp)

def serching(alpha, s):
    global k
    for i in range(s, len(first_str), 1):
        k=-99
        if first_str[i] == alpha:
            if dp[i] == 0:
                dp[i] = 1
            else:
                k = i
                break
    if k != -99:
        for i in range(k, len(first_str), 1):
            dp[i] = dp[i] + 1

for i in range(1, len(second_str)):
    serching(second_str[i], i)
    print(dp)

print(max(dp))
            
