#include "triples.h"
#include <algorithm>
#include <set>
#include <iostream>
bool works(int i,int j, int k,const std::vector<int>& H) {
    if( i >= j || j >= k) return false;
    int d[3] = {j-i,k-j,k-i};
    int h[3] = {H[i],H[j],H[k]};
    std::sort(d,d+3);
    std::sort(h,h+3);
    if (d[0] == h[0] && d[1] == h[1] && d[2] == h[2]) {
        std::cerr << i << " " << j << " " << k << "\n";
        return true;
    }
    return false;
} 
/*
    either: 
*/

long long count_triples(std::vector<int> H) {
    std::cerr << "bruteforce count_triples(...)\n";
    const int N = H.size();
    long long o = 0;
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            int h[3] = {H[i],H[j],-1};
            int d[3] = {j-i,-1,-1};
            for(int k : std::set<int>{i+H[i],i+H[j],j+H[i],j+H[j]}) {
                o += works(i,j,k,H);
            }
            
        }
    }
    std::cerr << " = " << o << "\n";
    return o;
}



std::vector<int> construct_range(int M, int K) {
    return {};
}