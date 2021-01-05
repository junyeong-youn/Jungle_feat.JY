import sys

sys.stdin = open("input.txt", "r")

N = int(sys.stdin.readline())
nums = list(map(int, sys.stdin.readline().split()))
X = []
Y = []
ans = []
fans = []
n = 0

nums.reverse()

while n < N:
    m = n
    if nums[n] == max(nums):
        ans.append(0)
    elif n == N-1:
        ans.append(0)
    else:
        while nums[n] >= nums[m]:
            if nums[n] > nums[m+1]:
                m+=1
            else:
                ans.append(m+1)
                break
    n+=1

ans.reverse()

for a in ans:
    if a == 0:
        fans.append(0)
    else:
        fans.append(N-a)

for f in fans:
    print(f,end=" ")
