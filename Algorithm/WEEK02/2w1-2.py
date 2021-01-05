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

N = int(sys.stdin.readline())
X = list(map(int, sys.stdin.readline().split()))
M = int(sys.stdin.readline())
Y = list(map(int, sys.stdin.readline().split()))
i=0

X.sort()

while i<M:
    result = binary_search(X, Y[i], 0, N-1)
    if result == None:
        print(0)
    else:
        print(1)
    i+=1
