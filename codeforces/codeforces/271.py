def sep(y):
	num = [0, 0, 0, 0]
	num[3] = y // 1000
	num[2] = (y % 1000) //100
	num[1] = (y % 100) // 10
	num[0] = y % 10
	for i in range(1, 4):
		for j in range(0, i):
			if num[i] == num[j]:
				return(j)
	return -1
	
y = int(input())
y = y + 1
mat = [1, 10, 100]
while True:
	z = sep(y)
	if(z < 0):
		break
	y = y + mat[z] - y % mat[z]
print(y)
		
