import sys

sys.stdin = open("input.txt", "r")

input = sys.stdin.readline

def divide(k, a, b, c):
    if a > c:
        k = a
    else:
        k = a ** 2
        b = b - 1
    while True:
        if b == 0:
            if k > c:
                k = k % c
            else:
                k = k
            break
        elif k > c:
            k = k % c
        else:
            b = b - 1
            k = k * a

    return k

a, b, c = list(map(int, input().split()))

k = 1

if b % 2 == 0:
    a = a ** 2
    b = b / 2
else:
    k = a
    b = (b - 1) / 2
    a = a ** 2

while True:

    if a>c:
        a = a % c
        if a == 1:
            print(1)
            break
        elif a == 0:
            print(0)
            break
        elif b == 0:
            print(k%c)
            break
        elif b % 2 == 0:
            a = a ** 2
            b = b / 2
        else:
            k = (k * a) % c
            b = (b - 1) / 2
            a = a ** 2
    else:
        if a == 1:
            print(1)
            break
        elif a == 0:
            print(0)
            break
        elif b == 0:
            print(k%c)
            break
        break
