count = 0
n = 212440

array = [500, 100, 50, 10]

for coin in array:
    count = count + n // coin
    n = n % coin

print(count)

-------------------------------------

N=25
K=5
count = 0

while True:
    if N == 1:
        break
    elif N%K == 0:
        N = N//K
        count += 1
    else:
        N = N-1
        count += 1
print(count)

-------------------------------------

N = 4

i=0

X = [0, 2, 9, 8, 4]
answer = 0
while i<N:
    if X[i] == 0 or X[i+1] ==0:
        answer = answer + X[i] + X[i+1]
    else:
        answer = answer * X[i+1]
    i+=1

print(answer)

----------------------------------------------

data = list(map(int, input().split()))

result = int(data[0])

for i in range(1, len(data)):
    num = int(data[i])
    if num <=1 or result<=1:
        result = result + num
    else:
        result = result * num

print(result)

--------------------------------------------------

N = int(input())
count = 0

for x in range(N+1):
    for y in range(60):
        for k in range(60):
            if '3' in str(x) + str(y) +str(k):
                count +=1
print(count)

-------------------------------------------------------

n = int(input())
x, y = 1, 1
plans = list(map(str,input().split()))

dx = [0,0,-1,1]
dy = [-1,1,0,0]
move = ['L', 'R', 'U', 'D']

for plan in plans:
    for i in range(len(move)):
        if plan == move[i]:
            nx = x + dx[i]
            ny = y + dy[i]
    if nx < 1 or ny <1 or ny > n or nx > n:
        continue
    x=nx
    y=ny

print("%d, %d" % (x,y))

-------------------------------------------

graph = [
    [],
    [2,3,8],
    [1,7],
    [1,4,5],
    [3,5],
    [3,4],
    [7],
    [2,6,8],
    [1,7]
]

visited = [False] * 9

def dfs(graph, v, visited):
    visited[v] = True
    print(v, end=' ')
    for i in graph[v]:
        if not visited[i]:
            dfs(graph, i, visited)

dfs(graph, 1, visited)

-------------------------------------------


from collections import deque

graph = [
    [],
    [2,3,8],
    [1,7],
    [1,4,5],
    [3,5],
    [3,4],
    [7],
    [2,6,8],
    [1,7]
]

visited = [False] * 9

def bfs(graph, start, visited):

    queue = deque([start])
    visited[start] = True

    while queue:
        v = queue.popleft()
        print(v, end= ' ')
        for i in graph[v]:
            if not visited[i]:
                queue.append(i)
                visited[i] = True

bfs(graph, 1, visited)


---------------------------------

import sys
import  heapq
input = sys.stdin.readline

def heapsort(iterable):
    h = []
    result = []
    for value in iterable:
        heapq.heappush(h, value)
    for i in range(len(h)):
        result.append(heapq.heappop(h))
    return result

n= int(input())
arr = []

for i in range(n):
    arr.append(int(input()))

res = heapsort(arr)
for i in range(n):
    print(res[i])
