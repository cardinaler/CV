sub = ['a']
sub_l = 1

def string_modif():
	global sub, sub_l
	all_change = 1
	for i in range(sub_l):
		if sub[i] != 'z':
			all_change = 0
			break
	if all_change:
		for i in range(sub_l):
			sub[i] = 'a'
		sub.append('a')
		sub_l += 1
	else:
		tmp = sub_l - 1
		while True:
			if sub[tmp] == 'z':
				sub[tmp] = 'a'
				tmp -= 1
			else:
				sub[tmp] = chr( ord(sub[tmp]) + 1)
				break

def s_find():
	


t = int(input())
for i in range(t):
	n = int(input())
	w = input()
	sub = ['a']
	sub_l = 1
	flag = 0
	while True:
		sub_there = 0
		for i in range(n):
			flag = 1
			if sub[0] == w[i]:
				for j in range(1, sub_l):		
					if i + j >= n or sub[j] != w[i + j]
						flag = 0
						break
				if flag:
					sub_there = 1
					break		
		if sub_there:
			string_modif()
		else:
			for i in range(sub_l):
				print(sub[i], end = '')
			print('')
			break
