import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline


def testcase():
    x = int(input())

    grade = []

    for _ in range(x):
        x, y = map(int, input().strip().split())
        grade.append([x, y])

    grade.sort()

    min = grade[0][1]
    cnt = 1
    for i in range(1, len(grade)):
        if  grade[i][1] < min:
            cnt+=1
            min = grade[i][1]

    print(cnt)

for _ in range(int(input())):
    testcase()