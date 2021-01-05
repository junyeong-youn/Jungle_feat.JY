C = int(input())
n = 0
while n < C:
    n += 1
    cs = list(map(int, input().split()))
    k = cs[0]
    del cs[0]
    print(cs)
    print(k)
    Max = 0
    for c in cs:
        Max = Max + c
    avr = Max / k
    print(avr)
    D = []
    for c in cs:
        if c > avr:
            D.append(c)
    Num = len(D) / k * 100
    Numx = round(Num, 3)
    print(Numx, end = '')
    print('%')