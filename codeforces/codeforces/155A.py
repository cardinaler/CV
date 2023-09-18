n = int(input())
a = list(map(int, input().split()))
maximus = a[0]
minimus = a[0]
counter = 0
for i in range(1, n):
	if a[i] > maximus:
		maximus = a[i]
		counter += 1
	if a[i] < minimus:
		minimus = a[i]
		counter += 1
print(counter)
	
	
