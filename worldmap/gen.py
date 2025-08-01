import random

N = 100
M = (N*(N-1))//2
p = list(range(1,N+1))
random.shuffle(p)
e: set[tuple[int,int]] = set()
for i in range(1,N):
    e.add(tuple(sorted((random.choice(p[:i]),p[i]))))

assert M <= (N*(N-1))//2
if M >= (N*(N-1))//4:
    ed = [(i,j) for i in range(1,N+1) for j in range(i+1,N+1)]
    random.shuffle(ed)
    while len(e) < M:
        e.add(ed.pop())
else:
    while len(e) < M:
        v = tuple(sorted((random.randint(1,N),random.randint(1,N))))
        if v[0] != v[1]: e.add(v)

print(N,M)
for x,y in e:
    print(x,y)
# for i in range(1,N):
#     print(i,i+1 )