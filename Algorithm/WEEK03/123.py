import sys
from collections import deque

sys.stdin = open("input.txt", "r")
input = sys.stdin.readline

N, line_num, start = list(map(int, input().split()))

graph = [[] for _ in range(N+1)]

for _ in range(line_num):
    node_start, node_end = list(map(int, input().split()))
    graph[node_start].append(node_end)

print(graph)
for i in graph:
    i.sort()

print(graph)