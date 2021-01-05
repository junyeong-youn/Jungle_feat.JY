x, y, w, h = map(int, input().split())

a = w - x
b = h - y
c = x
d = y

min = min(a, b, c, d)

print(min)