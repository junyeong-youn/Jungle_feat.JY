import sys

sys.stdin = open("input.txt" , "r")
input = sys.stdin.readline

N = int(input())
n = 1

data = []

data.append(int(input()))

while n < N:
    a = int(input())
    if a >= data[-1]:
        if a > max(data):
            data.clear()
            data.append(a)
        else:
            data.pop()
            data.append(a)
    else:
        data.append(a)
    n+=1

print(data)
data_set = set(data)
data = list(data_set)

print(len(data))
