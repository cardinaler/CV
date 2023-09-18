n, k = map(int, input().split())
a = [0]*n
a = list(map(int, input().split()))
sig = 0
ind = 1
for i in range(k):
    sig = sig + a[i]
ind = k - 1 - k + 2
least = sig
for i in range(k, n):
    sig = sig + a[i] - a[i - k]
    if sig < least:
        least = sig
        ind = i - k + 2
print(ind)
