def num_of_zeros(s):
	amount = 0
	for i in range(len(s)):
		if s[i] == '0':
			amount += 1
	return amount

def found_010(s):
	n = len(s)
	score = 0
	c = '0'
	for i in range(n):
		if s[i] == c:
			if c == '0':
				c = '1'
			else:
				c = '0'
				pos = i
			score += 1
			if score == 3:
				return pos				
	return 0

t = int(input())
for i in range(t):
	s = list(map(str, input()))
	zeros = num_of_zeros(s)
	c = '0'
	if 2 * num_of_zeros >= len(s):
		while True:
			pos = found_010(s)
			if pos != 0:
				s[pos] = '0'
#			else:
#				pos = found_101(s)
#				if pos != 0
			else:
				print(*s)
				exit()
	else:
		while True:
			if found_101(s):
				delete_0(s)
			elif found_010(s):
				delete_0(s)
			else:
				print(*s)
				exit()

