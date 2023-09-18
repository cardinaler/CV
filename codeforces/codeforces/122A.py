def get_next_lucky_n(past_lucky_n):
	N = 10
	next_lucky_n = 0
	counter = 1
	while True:
		dig = past_lucky_n % N
		if dig == 4:
			next_lucky_n = next_lucky_n + counter * 7
			next_lucky_n = next_lucky_n + (past_lucky_n - 4) * counter 
			break
		elif dig == 7:
			next_lucky_n = next_lucky_n + counter * 4
		elif past_lucky_n == 0:
			next_lucky_n = next_lucky_n + counter * 4
			break
		past_lucky_n = past_lucky_n // N
		counter = counter * N
	return next_lucky_n

n = int(input())
num = 4
while num <= n:
	if n % num == 0:
		print('YES')
		exit(0)
	num = get_next_lucky_n(num)
print('NO')


