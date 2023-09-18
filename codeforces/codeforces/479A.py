a = int(input())
b = int(input())
c = int(input())
maximus = a + b + c
if a * (b + c) > maximus:
	maximus = a * (b + c)
if (a + b) * c > maximus:
	maximus = (a + b) * c
if a * b * c > maximus:
	maximus = a * b * c
print(maximus)
