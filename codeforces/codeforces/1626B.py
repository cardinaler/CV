t = int(input())

for i in range(t):
	x = input()
	length = len(x)
	found = 0
	for j in range(length - 2, -1, -1):
		tmp = int(x[j]) + int(x[j + 1])
		if tmp > 9:
			for k in range(j):
				print(x[k], end = '')
			print(tmp // 10, tmp % 10, end = '', sep = '')
			for k in range(j + 2, length):
				print(x[k], end = '')
			print()
			found = 1
			break
	if found:
		continue	
	for j in range(length - 1):
		tmp = int(x[j]) + int(x[j + 1])
		if tmp > 0:
			for k in range(j):
				print(x[k], end = '')
			print(tmp, end = '')
			for k in range(j + 2, length):
				print(x[k], end = '')
			print()
			break
	

		
			

