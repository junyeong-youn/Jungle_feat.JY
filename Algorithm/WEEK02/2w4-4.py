import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

N = int(input())
n = 0
fluid_list = list(map(int, input().split()))
mix_list = []
fluid_list.sort()
cnt = 0
while n < N-1:
    cnt+=1

    if abs(fluid_list[-1]) > abs(fluid_list[0]):
        mix_list.append([fluid_list[0], fluid_list[-1], abs(fluid_list[0]+fluid_list[-1])])
        fluid_list.pop()

    elif abs(fluid_list[0] - (fluid_list[0] + fluid_list[-1])) < abs(fluid_list[-1] - (fluid_list[0] + fluid_list[-1])):
        mix_list.append([fluid_list[0], fluid_list[-1], abs(fluid_list[0] + fluid_list[-1])])
        fluid_list.pop(0)
    else:
        mix_list.clear()
        mix_list.append([fluid_list[0], fluid_list[-1], 1])
        break
    n+=1


mix_list.sort(key=lambda x: x[2])

print(mix_list[0][0], end = " ")
print(mix_list[0][1])
print(cnt)