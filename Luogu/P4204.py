from fractions import *
t, n, d = map(int, input().split())
array = list(map(int, input().split()))
s = sum(array)
ans = Fraction(1)
for i in range(n):
	x, y = map(int, input().split())
	y -= 1
	ans *= Fraction(array[y], s)
	array[y] += d
	s += d
print(ans)
