import sys
import heapq

sys.stdin = open("input.txt", "r")

def heap_sort(nums):
    heap = []
    for num in nums:
        heapq.heappush(heap, num)

    sorted_nums = []
    while heap:
        sorted_nums.append(heapq.heappop(heap))
    return sorted_nums

N = int(sys.stdin.readline())
firstlist = []
n = 0
m= 0
max = 0

while n<N:
    n+=1
    x = int(sys.stdin.readline())
    firstlist.append(x)
firstlist = heap_sort(firstlist)

while m<len(firstlist):
    max = max + firstlist[m]*(len(firstlist)-m)
    m+=1
if N == 1:
    print(0)
else:
    print(max-firstlist[0])