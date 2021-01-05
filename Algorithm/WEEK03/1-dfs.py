import sys

sys.stdin = open("input.txt", "r")
input = sys.stdin.readline

def dfs(graph, v, visited):
    visited[v] = True
    print(v, end=' ')

    for i in graph[v]:
        if not visited[i]:
            dfs(graph, i, visited)

N, line_num, start = list(map(int, input().split()))

graph = [[] for _ in range(N+1)]

for _ in range(line_num):
    node_start, node_end = list(map(int, input().split()))
    graph[node_start].append(node_end)

visited = [False] * (N+1)

dfs(graph, 1, visited)