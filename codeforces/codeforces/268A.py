n = int(input())
counter = 0
col = [0] * n
for i in range(n):
	col[i] = list(map(int, input().split()))
for i in range(n):
	for j in range(n):
		if col[i][0] == col[j][1]:
			counter += 1
print(counter)
	



