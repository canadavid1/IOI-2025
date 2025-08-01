
def int_or(a):
    try:
        return int(a)
    except:
        return None

import random
f = lambda i: (i-[0,2,12,22][(i+1)%4])
N = 200000
# H = list(map(int_or,"4 1 4 - - - 6 5 - - -  11  4  -  -  5  -  -  -  -  -  -  4".split()))
# H += [None]*(N-len(H))
# for i in range(N):
#     if H[i] == None: H[i] = f(i)
H = [random.choice((random.randint(1,5),max(i-2,1),max(N-i-2,1))) for i in range(N)]
print(1)
print(N)
print(*H)