import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N, M = list(map(int, input().split()))
trees = list(map(int, input().split()))

low, high = 1, 1000000000

while low <= high:
    mid = (high + low) // 2
    num = 0
    for i in trees:
        if i - mid > 0:
            num = num + (i - mid)
        else:
            num = num + 0
    if num >= M:
        low = mid + 1
    else:
        high = mid - 1
    print(num)
    print(high)

