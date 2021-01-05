import sys
from collections import deque

sys.stdin = open("./input.txt", "r")
input = sys.stdin.readline

def bfs(graph, start, visited):
    queue = deque([start])
    visited[start] = True
    
    while queue:
        v = queue.popleft()
        print(v, end=' ')
        for i in graph[v]:
            if not visited[i]:
                queue.append(i)
                visited[i] = True

N, line_num, start = list(map(int, input().split()))

graph = [[] for _ in range(N+1)]

for _ in range(line_num):
    node_start, node_end = list(map(int, input().split()))
    graph[node_start].append(node_end)
    graph[node_end].append(node_start)

for i in graph:
    i.sort()

visited = [False] * (N+1)

bfs(graph, start, visited)