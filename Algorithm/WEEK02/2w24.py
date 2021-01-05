import sys
import heapq

sys.stdin = open("input.txt", "r")

N = int(sys.stdin.readline())
n = 0
data = []

while n<N:
    n+=1
    x = int(sys.stdin.readline())
    if x != 0:
        heapq.heappush(data, (-x, x))
    elif x == 0:
        if len(data) == 0:
            print(0)
        else:
            print(heapq.heappop(data)[1])

