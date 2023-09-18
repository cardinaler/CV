t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    tmp = a
    tmp.sort()
    b = [0] * n
    b[0] = 1
    for i in range(1, n):
        dif = b[i - 1] + a[i - 1] - a[i]
        if dif < 0:
            
