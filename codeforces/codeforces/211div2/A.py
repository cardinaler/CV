n = int(input())
tmp = 1
while tmp != 0:
	curr = n % 10
	n = n // 10
	if curr >= 5:
		curr = curr - 5
		print('-O|', end = '')
	else:
		print('O-|', end = '')
	print('O' * curr + '-' + 'O' * (4 - curr))
	tmp = n

