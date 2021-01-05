import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

stack = []
razer_position = []
par_list = list(map(str, input().rstrip()))
bar_list = []
n = 0
m = 1
k = 0
while m < len(par_list):
    if par_list[m-1] == '(' and par_list[m] == ')':
        razer_position.append(m-1)
    m+=1

while n < len(par_list):
    if par_list[n] == '(':
        bar_list.append(1)
    elif par_list[n] == ')':
        bar_list.append(-1)
    n+=1

k=0
while k < len(razer_position):
    razer_position[k] = razer_position[k] -k
    k+=1

for i in razer_position:
    bar_list[i] = 0
    bar_list.pop(i+1)

b=0
cnt = 0
l=0
while l < len(bar_list):
    if bar_list[l] == 1:
        b = b + 1
    elif bar_list[l] == -1:
        cnt = cnt + 1
        b = b -1
    elif bar_list[l] == 0:
        cnt = cnt + b
    l += 1

print(cnt)