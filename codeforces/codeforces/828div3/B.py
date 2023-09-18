t = int(input())
for i in range(t):
    n, q = map(int, input().split()) #len, queries num
    arr = list(map(int, input().split()))
    odds = 0
    evens = 0
    sum_ = 0
    for k in range(n):
            if arr[k] % 2 == 0:
                evens += 1
            else:
                odds += 1
            sum_ = sum_ + arr[k]
    for j in range(q):
        type_, x = map(int, input().split()) 
        sum_ = sum_ + x *(evens * (1 - type_) + odds * type_)
        if x % 2 == 1 and type_ == 0:
            odds = odds + evens
            evens = 0
        if x % 2 == 1 and type_ == 1:
            evens = odds + evens
            odds = 0
        print(sum_) 
    

        
       
