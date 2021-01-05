import sys

sys.stdin = open("input.txt" , "r")

input = sys.stdin.readline

N = int(input())
A = []
B = []
n = 0

while n < N:
    if n == 0:
        A.append(int(input()))
    else:
        high = int(input())
        if min(A) <= high:
            while min(A) <= high:
                A.pop()
                if A == []:
                    A.append(high)
                    break
            if high == A[-1]:
                A.pop()
                A.append(high)
            else:
                A.append(high)
        else:
            A.append(high)
    n+=1

print(len(A))