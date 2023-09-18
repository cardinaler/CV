t = int(input())
def how_many_2(num):
    counter = 0
    while num % 2 == 0:
        counter += 1
        num = num // 2
    return counter
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    need = n
    z = 0
    for i in range(n):
        need = need - how_many_2(a[i])
    op_num = 0
    if need <= 0:
        print(op_num)
        z = 1
    else:
        s = [0] * (n + 1)
        for i in range(1, n + 1):
            s[i] = how_many_2(i)
        s.sort()
        for i in range(n, 0, -1):
            op_num += 1
            need = need - s[i]
            if(need <= 0):
                print(op_num)
                z = 1
                break
    if not z:
        print(-1)
    
