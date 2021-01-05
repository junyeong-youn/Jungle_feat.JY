import sys

sys.stdin = open("input.txt", "r")

N = int(sys.stdin.readline())
List = []
circle = []
for _ in range(N):
    X = list(map(int, sys.stdin.readline().split()))
    List.append(X)

print(List)

for i in List:
    i.append(i[0]-i[1])
    i.append(i[0]+i[1])
print(List)

List.sort(key=lambda x:x[1])
List.reverse()

print(List)

for i in List:
    circle.append([i[2], i[3]])

print(circle)
cnt = 0
n=1

while n < N-2:

    while True:
        if circle[n][1] == circle[n+1][0]:
            circle[n][1] = circle[n+1][1]
            circle.pop(n+1)
        elif circle[n-1] == circle[n]:
            cnt = cnt + 1
            break
        else:
            break
    n+=1

print(cnt)