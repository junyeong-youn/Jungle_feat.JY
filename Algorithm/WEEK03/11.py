from collections import deque
import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N, line_num = list(map(int, input().split()))

indegree = [0] * (N + 1)
# 진입차수(0부터)
graph = [[] for i in range(N+1)]
# 각 노드 간선정보 리스트

for _ in range(line_num):
    start, end = map(int, input().split())
    graph[start].append(end)
    indegree[end] += 1

def topology_sort():
    result = []
    q = deque()
    for i in range(1, N + 1):
        if indegree[i] == 0:
            q.append(i)
    while q:
        now = q.popleft()
        result.append(now)
        for i in graph[now]:
            indegree[i] -= 1
            if indegree[i] == 0:
                q.append(i)
    for i in result:
        print(i, end=" ")

topology_sort()