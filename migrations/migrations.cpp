#include "migrations.h"


/*
    to get some longest path: choose the two oldest candidates
    upon update, at one of the previous is still included, and the other is the new node
    => Z = 2, M=N solution

*/

std::vector<int> P{{0}},d{{0}},gp{{0}};
int curA=0,curD=0;
int lca(int a,int b) {
    int ct = 0;
    if (d[a] < d[b]) std::swap(a,b);
    while(d[a] > d[b]) 
        if (d[gp[a]] >= d[b]) a = gp[a];
        else a = P[a];
    while (a != b)
        if (gp[a] != gp[b]) a = gp[a],b=gp[b];
        else a = P[a],b=P[b];
    return a;
}
int dist(int a,int b) {
    return d[a] + d[b] - 2*d[lca(a,b)];
}

// using the last M messages, encode which two
// can change during, but then do some skip-code thing
/*
    subtask 1:
    last M messages encode the bits of the end. if it suddenly changes to current node, encode with 0.


*/
const int M = 16; 
int send_message(int N, int i, int Pi) { // this can retain information across calls
    P.push_back(Pi);
    d.push_back(d[Pi]+1);
    if(d[gp[gp[Pi]]] - 2*d[gp[Pi]] + d[Pi] == 0) gp.push_back(gp[gp[Pi]]);
    else gp.push_back(Pi);
    if (d[i] > curD) {curA = i;curD = d[i];}
    int idx = N-1-i;
    if (idx >= M) return 0;
    if(curA == i) return 2;
    if (curA >= N-M) return 0;
    return (curA >> idx) & 1;
}

std::pair<int, int> longest_path(std::vector<int> S) {
    int curA = 0;
    const int N = S.size();
    for(int idx = 0; idx < M; idx++) {
        auto v = S[N-1-idx];
        if(v == 2) return {0,N-1-idx};
        curA |= v << idx;
    }
    return {0,curA};
}
