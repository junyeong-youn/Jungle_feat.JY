import sys

sys.stdin = open("input.txt", "r")

N = int(sys.stdin.readline())
nums = list(map(int, sys.stdin.readline().split()))
n = 0
cut = 0

nums.reverse()

ans = []

while n < len(nums):
    if nums[n] < nums[n+1]:
        ans.append(n+1)
    elif nums[n] > num[n+k]
    else:
        m=n
        l=0
        while l < len(nums)-n:
            if nums[n] >= nums[m+1]:
                l += 1
            else:
                ans.append(n+m)
                break

            m += 1
    n+=1
print(ans)