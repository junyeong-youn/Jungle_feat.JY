import sys

sys.stdin = open("JY/input.txt", "r")

input = sys.stdin.readline


def testcase():

    x = int(input())

    grade = []

    for _ in range(x):
        x, y = map(int, input().strip().split())
        grade.append((x, y))

    grade.sort()
    grade.reverse()

    while True:

        for i in range(len(grade)-1):
            if grade[i][1] >= grade[i+1][1]:
                grade.pop(i)
                break 
            if i == len(grade) - 2:
                print(len(grade))
                return 

for i in range(int(input())):
    testcase()
