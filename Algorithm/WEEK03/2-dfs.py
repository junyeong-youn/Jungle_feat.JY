import sys
from collections import deque

input = sys.stdin.readline


def dfs(graph, v, visited):
    visited[v] = True
    virused_computerlist.append(v)

    for i in graph[v]:
        if not visited[i]:
            dfs(graph, i, visited)

N = int(input())
line_num = int(input())

graph = [[] for _ in range(N + 1)]
virused_computerlist = []

for _ in range(line_num):
    node_start, node_end = list(map(int, input().split()))
    graph[node_start].append(node_end)
    graph[node_end].append(node_start)

for i in graph:
    i.sort()

visited = [False] * (N + 1)

dfs(graph, 1, visited)

if len(virused_computerlist) <= 1:
    print(1)
else:
    print(len(virused_computerlist)-1)