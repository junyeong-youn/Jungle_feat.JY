import sys
from collections import deque

sys.stdin = open("input.txt", "r")

N, K = map(int, sys.stdin.readline().split())

list = deque()
n = 0
m = 0
Josephus = []


while n < N:
    n+=1
    list.append(n)

while True:
    if len(list) == 0:
        break
    else:
        while m < K-1:
            m+=1
            list.append(list.popleft())
        Josephus.append(list.popleft())
        m = 0

a = (", ".join(map(str, Josephus)))
print('<{}>'.format(a))

