import random
N=10
P = [1]
for i in range(N):
    P.append(P[-1]+2)
P.reverse()
print(N)
print(*P)