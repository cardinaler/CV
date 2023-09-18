t = int(input())
for i in range(t):
    n = int(input())
    s = input()
    now = 0
    while now < n - 1:
        c = s[now]
        print(c, end = '')
        for j in range(now + 1, n):
            if c == s[j]:
                now = j + 1
                break
    print()
        