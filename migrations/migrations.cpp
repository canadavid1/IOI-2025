#include "migrations.h"


std::vector<int> P = {-1};
int send_message(int N, int i, int Pi) { // this can retain information across calls
    P.push_back(Pi);
    if (i < N-1) return 0;
    std::vector<int> d(N);
    d[0] = 0; 
    int mi=0;
    for(int j = 1; j < N; j++) {
        d[j] = d[P[j]] + 1;
        if (d[j] > d[mi]) mi = j;
    }
    return mi-2;
}

std::pair<int, int> longest_path(std::vector<int> S) {
    return {0, S.back()+2};   
}
