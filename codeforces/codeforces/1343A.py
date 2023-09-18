t = int(input())
# x * (2**k - 1) = n
for i in range(0, t):
	n = int(input())
	k = 2
	while True:
		tmp = 2 ** k - 1
		if n % tmp == 0:
			print(n // tmp)
			break
		k += 1
