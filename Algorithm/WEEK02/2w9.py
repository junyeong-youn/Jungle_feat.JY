import sys

sys.stdin = open("input.txt", "r")

while True:
    H_list = list(map(int, sys.stdin.readline().split()))
    N = H_list.pop(0)
    sums = []

    if N == 0:
        break

    if min(H_list) != 0:
        sums.append((min(H_list))*N)


    sums.append(H_list[0])
    n = 0
    while n < N:
        sums.append(H_list[n])
        m = n
        k = 2
        l = 0
        while l < N-n-1:
            if H_list[n] <= H_list[m+1]:
                sums.append(H_list[n] * (k))
                k += 1
                m += 1
            else:
                break
            l+=1
        n += 1

    H_list.reverse()
    if N == 0:
        break

    if min(H_list) != 0:
        sums.append((min(H_list)) * N)

    sums.append(H_list[0])
    n = 0
    while n < N:
        sums.append(H_list[n])
        m = n
        k = 2
        l = 0
        while l < N - n - 1:
            if H_list[n] <= H_list[m + 1]:
                sums.append(H_list[n] * (k))
                k += 1
                m += 1
            else:
                break
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
            l += 1
        n += 1

    print(max(sums))