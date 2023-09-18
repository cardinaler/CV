n, a, b, c = map(int, input().split())
s = [0] + [-1e9] * 5000
for i in range(1, n + 1):
	max_ = max(s[i - a], s[i - b], s[i - c])
	s[i] = max_ + 1
print(s[n])
