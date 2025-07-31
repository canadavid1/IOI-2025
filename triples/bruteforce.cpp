#include "triples.h"
#include <algorithm>

long long count_triples(std::vector<int> H) {
    const int N = H.size();
    long long o = 0;
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            for(int k = j+1; k < N; k++) {
                int d[3] = {j-i,k-j,k-i};
                int h[3] = {H[i],H[j],H[k]};
                std::sort(d,d+3);
                std::sort(h,h+3);
                if (d[0] == h[0] && d[1] == h[1] && d[2] == h[2]) o++;
            }
        }
    }
    return o;
}



std::vector<int> construct_range(int M, int K) {
    return {};
}