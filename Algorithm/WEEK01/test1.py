x = int(input())

m = 0

def Rotation(x):
    return ((x//10+x-((x//10)*10))%10) + ((x-((x//10)*10))*10)

a = x
if x == 0:
    print(1)
else:
    while m < 1000000:
        x=Rotation(x)
        m+=1
        if Rotation(x) == a:
            break

    print(m+1)


