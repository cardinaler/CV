A, K, B , M, X = map(int, input().split())
L = 1
R = X
while L < R:
    aver = (L + R) // 2
    if (A * (aver - aver // K)) + (B * (aver - aver // M)) < X:
        L = aver + 1
    else:
        R = aver
print(L)