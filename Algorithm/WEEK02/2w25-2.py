import sys
import heapq

sys.stdin = open("input.txt", "r")
input = sys.stdin.readline

N = int(input())
n = 0
large_list = []
small_list = []

for _ in range(N):
    num = int(input())
    if len(large_list) == len(small_list):
        heapq.heappush(large_list, (-num, num))
    else:
        heapq.heappush(small_list, (num, num))

    if small_list and large_list[0][1] > small_list[0][1]:
        temp_large = heapq.heappop(large_list)[1]
        temp_small = heapq.heappop(small_list)[1]
        heapq.heappush(large_list, (-temp_small, temp_small))
        heapq.heappush(small_list, (temp_large, temp_large))
    print(large_list[0][1])

