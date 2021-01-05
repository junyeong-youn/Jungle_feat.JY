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

while n<N:
    n+=1
    x = int(sys.stdin.readline())
    firstlist.append(x)
    if len(heap_sort(firstlist))%2 == 0:
        print(heap_sort(firstlist)[(len(heap_sort(firstlist))//2)-1])
    else:
        print(heap_sort(firstlist)[(len(heap_sort(firstlist))//2)])

