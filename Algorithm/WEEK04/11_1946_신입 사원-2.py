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
    grade.reverse()

    indexlist = [0]
    cnt = 0

    for j in range(1, x):
        for i in range(x):    
            if grade[i][1] == j:
                indexlist.append(i)

    for x in range(len(indexlist)-1):
        if indexlist[x] < indexlist[x+1]:+
            cnt +=1

    print(cnt)

for _ in range(int(input())):
    testcase()
