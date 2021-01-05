import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline

meeting_num = int(input())
timetable = []
for _ in range(meeting_num):
    start, end = map(int, input().rstrip().split())
    timetable.append((start, end))

timetable.sort()
possible_table = []
possible_table.append(timetable[0])

for i in range(1, len(timetable)):
    if timetable[i][1] < possible_table[-1][1]:
        possible_table.pop()
        possible_table.append(timetable[i])
    elif timetable[i][0] >= possible_table[-1][1]:
        possible_table.append(timetable[i])

print(len(possible_table))