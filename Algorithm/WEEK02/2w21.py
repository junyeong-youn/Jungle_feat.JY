import sys
from collections import deque

Q = deque()

N = int(sys.stdin.readline())

for i in range(N):
    Q.append(i+1)

if Q == deque([1]):
    print(1)
else:
    while True:
        Q.popleft()
        Q.append(Q.popleft())
        if len(Q) == 1:
            break
    print(Q.pop())