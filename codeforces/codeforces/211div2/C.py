s = input()
l = len(s)
in_word = 0
z = 1
print(s[0], end = '')
if l == 1:
    exit()
print(s[1], end = '')
if s[0] == s[1]:
    in_word = 1
    z = not z
for i in range(2, l):
    if s[i] == s[i - 1] and in_word == 0:
        in_word = 1
        if z:
            print(s[i], end = '')
        z = not z
        
    elif s[i] != s[i - 1]:
        in_word = 0
        print(s[i], end = '')
        if s[i - 1] != s[i - 2]:
            z = 1
print('')
    

