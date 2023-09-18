t = int(input())
for _ in range(t):
    n, c = map(str, input().split())
    n = int(n)
    s = input()
    s = s + s
    n = n * 2   
    max_ = 0
    flag = False
    for i in range(0, n):
        if not flag and s[i] == c:
            tmp = i
            flag = not flag
        if flag and s[i] == 'g':
            if i - tmp > max_:
                max_ = i - tmp
            flag = not flag

    print(max_)
        