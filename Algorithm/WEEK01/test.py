#### 1, 2, 3 더하기

x = int(input())


# n 아래 수에 대한 조합을 구한다.
def plus(n):
    if n > 0:
        for i in range(1, 4):
            if i <= n:
                n -= i
                plus(n)
                n += i
    elif n == 0:
        global answer
        answer += 1


for i in range(x):
    answer = 0
    plus(int(input()))
    print(answer)
