
def int_or(a):
    try:
        return int(a)
    except:
        return None

import random
f = lambda i: (i-[0,2,10][(i+1)%3])
N = 20
H = list(map(int_or,"3 1 3 - - 5 4 - - -  3".split()))
H += [None]*(N-len(H))
for i in range(N):
    if H[i] == None: H[i] = f(i)
# H = [max(1,i) for i in range(N)]
print(1)
print(N)
print(*H)