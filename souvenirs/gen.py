import sys
import random
N=50
P = [1]
P.append(random.randint(P[-1]+1,P[-1]*2))
for i in range(2,N):
    P.append(random.randint(P[-1]+P[-2],max(int(P[-1]*1.1),P[-1]+P[-2]+1)))
P.reverse()
print(*P,file=sys.stderr)
if P[0] >= 10**15:
    print("bad generator",file=sys.stderr)
    exit(1)
print(N)
print(*P)