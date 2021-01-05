import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N, line_num = map(int, input().rstrip().split())

edge = [[] for _ in range(N+1)]
ret = []
visited = [False] * (N+1)

for _ in range(line_num):
    start, end = map(int, input().rstrip().split())
    edge[start].append(end)

def dfs(x):
    visited[x] = True
    for y in edge[x]:
        if not visited[y]:
            dfs(y)
    ret.append(x)

for i in range(1, N+1):
    if not visited[i] : dfs(i)

while ret : 
    print(ret.pop(), end =' ')