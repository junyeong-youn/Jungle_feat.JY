from itertools import combinations
import sys

sys.stdin = open("input.txt", "r")

def binary_search(arr, target, start, end):
    while start <= end:
        mid = (start + end) // 2
        if arr[mid][2] == target:
            return mid
        if arr[mid][2] > target:
            end = mid -1
        else:
            start = mid + 1
    return None

def sum(x):
    return x[0]+x[1]

N = int(sys.stdin.readline())
lists = list(map(int, sys.stdin.readline().split()))
c_list = combinations(lists, 2)
l_list = []
p_list = []
n=0

for c in c_list:
    l_list.append(list(c))

for l in l_list:
    l.append(sum(l))

l_list.sort(key=lambda  x:x[2])

result = binary_search(l_list, 0, 0, len(l_list)-1)
while n<10000:
    if result != None:
        break
    else:
        n += 1
        result = binary_search(l_list, n, 0, len(l_list)-1)
        result = binary_search(l_list, -n, 0, len(l_list)-1)
        continue

print(l_list[result][0], end = " ")
print(l_list[result][1])