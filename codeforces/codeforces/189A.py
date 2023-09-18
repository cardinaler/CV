n, a, b, c = map(int, input().split())
counter = 0
rest = 0
answer = 0
def div(N, divider):
	global counter, rest, answer
	if N % divider == 0:
		if counter + N // divider > answer:
			answer = counter + N // divider
		return 0
	else:
		counter = counter + N // divider
		rest = N % divider
		return 1
def step(N, divider):
	global counter, rest
	counter = counter - 1
	rest = N + divider
		

mini = min(a, b, c)
maxi = max(a, b, c)
mid = a + b + c - mini - maxi
if div(n, mini):
	while counter != 0:
		step(rest, mini)
		past = counter
		if div(rest, mid):
			while past != counter:
				step(rest, mid)
				past_r = rest
				if div(rest, maxi):
					rest = past_r
					counter = counter - rest // maxi
		else:
			break
print(answer)
			




	
	
