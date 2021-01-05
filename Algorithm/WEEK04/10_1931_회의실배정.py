import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

meeting_num = int(input())
timetable = []
for _ in range(meeting_num):
    start, end = map(int, input().rstrip().split())
    timetable.append((start, end))

timetable.sort()

time = [0 for _ in range(max(map(max, timetable))+1)]

for i in timetable:
    x, y = i
    for l in range(x, y, 1):
        time[l] = time[l] + 1


def cut(x, y):
    for i in range(x, y, 1):
        time[i] -= 1

while True:
    if max(time) == 1:
        print(len(timetable))
        exit()
    cntlist = [0 for _ in range(len(timetable))]
    mxl = list(filter(lambda x: time[x] == max(time), range(len(time))))
    for i in range(len(timetable)):
        x, y = timetable[i]
        cnt = 0
        for a in mxl:
            if x <= a <= y:
                cnt += 1
        cntlist[i] = cnt

    k = cntlist.index(max(cntlist))    

    x, y = timetable.pop(k)

    cut(x, y)
   