t = int(input())
for i in range(t):
    z = 1
    length = int(input())
    arr = list(map(int, input().split()))
    word = input()
    for j in range(length):
        tmp = arr[j]
        for k in range(length):
            if arr[k] == tmp:
                arr[k] = word[j];
    for j in range(length):
        if arr[j] != word[j]:
            print("NO")
            z = 0
            break
    if z:
        print("YES")
        
