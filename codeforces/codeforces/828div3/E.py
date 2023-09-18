# def gcd(a, b):
#     b = b % a
#     while b:
#         a, b = b, a
#         b = b % a
#     return a
t = int(input())
for _ in range(t):
    a, b, c, d = map(int , input().split())
    z = 1
    a_div = [0] * 1400
    b_div = [0] * 1400
    i = 1
    j = 0
    while i*i <= a:
        if a % i == 0:
            a_div[j] = i
            j += 1
            a_div[j] = a // i
            j += 1
        i += 1
    i = 1
    j = 0
    while i * i <= b:
        if b % i == 0:
            b_div[j] = i
            j += 1
            b_div[j] = b // i
            j += 1
        i += 1
    i = 0
    j = 0
    while a_div[i] != 0:
        while b_div[j] != 0:
            num = a_div[i] * b_div[j]  
            p = a * b // num
            y = p * (d // p)
            if not b < y <= d:
                j += 1
                continue
            x = num * (c // num)
            if not a < x <= c:
                j += 1
                continue
            z = 0
            print(x, y)
            break
        if not z:
            break
        j = 0
        i += 1
    if z:
        print(-1, -1)