import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N = int(input())
n=1
graph = [[] for _ in range(N+1)]
mother = []

for _ in range(N-1):
    start, end = map(int, input().strip().split())
    graph[start].append(end)
    graph[end].append(start)

visited = [False for _ in range(N+1)]
stack = [1]

while stack:
   
    a = stack.pop()
    visited[a] = True
    
    for i in graph[a]:
        if not visited[i]:
            stack.append(i)
            mother.append((a, i))
            

mother.sort(key=lambda x:x[1])


for i in mother:
    print(i[0])