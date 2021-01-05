def ha(num, start, object, sub):
    if num == 1:
        print("%d %d" % (start, object))
        return
    ha(num-1, start, sub,object)
    print("%d %d" % (start, object))
    ha(num-1, sub, object, start)

N = int(input())
K = 2 ** N - 1
print(K)
if N<=20:
    ha(N, 1, 3, 2)
else:
    pass
