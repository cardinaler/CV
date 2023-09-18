n = int(input())
max = 1
a = list(map(int, input().split()))
length = 1
for i in range(1, n):
	if a[i] >= a[i-1]:
		length = length + 1
	else:
		length = 1
	if length > max:
		max = length
print(max)

		
