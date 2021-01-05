import sys

sys.stdin = open("input.txt" , "r")
input = sys.stdin.readline

N = int(input())
num_list = []
stack = []
n = 1
m = 0

for _ in range(N):
    a = int(input())
    num_list.append(a)

num_list.reverse()

stack.append(num_list[0])

while n<N-1:
    m = n
    while m < N:
        if num_list[n-1] >= num_list[m]:
            m+=1
        else:
            stack.append(num_list[m])
            n = m + 1
            break

if max(num_list) == num_list[-1]:
    stack.append(max(num_list))


print(len(stack))