import sys
from collections import deque


sys.stdin = open("input.txt", "r")

N = int(sys.stdin.readline())
Q = deque()
for _ in range(N):
    command = str(sys.stdin.readline().strip())

    if command[0:4] == 'push':
        Q.append(int(command.replace('push ','')))

    elif command == 'pop':
        if len(Q) == 0:
            print(-1)
        else:
            print(Q.popleft())

    elif command == 'size':
        print(len(Q))

    elif command == 'empty':
        if len(Q) == 0:
            print(1)
        else:
            print(0)
    elif command == 'front':
        if len(Q) == 0:
            print(-1)
        else:
            print(Q[0])
    elif command == 'back':
        if len(Q) == 0:
            print(-1)
        else:
            print(Q[-1])


