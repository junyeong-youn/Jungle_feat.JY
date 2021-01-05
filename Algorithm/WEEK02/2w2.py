import sys

sys.stdin = open("input.txt", "r")

def binary_search(arr, target, start, end):
    while start <= end:
        mid = (start + end) // 2
        if arr[mid] == target:
            return mid
        if arr[mid] > target:
            end = mid -1
        else:
            start = mid + 1
    return None

def gain(tree_H, H):
    if tree_H <= H:
        return 0
    else:
        return tree_H-H

N, target = list(map(int, sys.stdin.readline().split()))
tree_highs = list(map(int, sys.stdin.readline().split()))
n = 0
m = 0
gains = 0
gains_list = []

H_list = list(range(1, max(tree_highs)+1, 1))

for i in H_list:
    while n < N:
        gains = gains + gain(tree_highs[n], i)
        n+=1
    gains_list.append(gains)
    gains = 0
    n=0

gains_list.reverse()
H_list.reverse()


result = binary_search(gains_list, target, 0, len(gains_list)-1)
while True:
    if result != None:
        break
    else:
        result = binary_search(gains_list, target + 1, 0, len(gains_list)-1)
        continue
print(H_list[result])