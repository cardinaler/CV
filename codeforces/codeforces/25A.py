n = int(input())
a = list(map(int, input().split()))

parity1 = a[0] % 2
parity2 = a[1] % 2

if parity1 != parity2:
	if parity1 == a[2] % 2:
		print(2)
	else:
		print(1)
	exit()
		
for i in range(2, n):
	if parity1 != a[i] % 2:
		print(i + 1)


