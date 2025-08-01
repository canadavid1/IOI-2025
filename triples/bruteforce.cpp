#include "triples.h"
#include <algorithm>
#include <set>
#include <iostream>
#include <iomanip>
bool works(int i,int j, int k,const std::vector<int>& H) {
    if( i >= j || j >= k || k >= H.size()) return false;
    int d[3] = {j-i,k-j,k-i};
    int h[3] = {H[i],H[j],H[k]};
    std::sort(d,d+3);
    std::sort(h,h+3);
    if (d[0] == h[0] && d[1] == h[1] && d[2] == h[2]) {
        // std::cerr << i << " " << j << " " << k << "\n";
        for(int _ = 0; _ < i; _++) std::cerr << "   ";
        std::cerr << std::setw(3) << i;
        for(int _ = i+1; _ < j; _++) std::cerr << "   ";
        std::cerr << std::setw(3) << j;
        for(int _ = j+1; _ < k; _++) std::cerr << "   ";
        std::cerr << std::setw(3) << k;
        for(int _ = k+1; _ < H.size(); _++) std::cerr << "   ";
        if(j-i == H[k] && k-j == H[i]) {
            std::cerr << "!!";
        }
        std::cerr << "\n";
        return true;
    }
    return false;
} 
/*
    either: 
*/

long long count_triples(std::vector<int> H) {
    std::cerr << "bruteforce count_triples(...)\n";
    for(int i = 0; i < H.size(); i++) std::cerr << std::setw(3) << i; std::cerr << "\n";
    for(int i = 0; i < H.size(); i++) std::cerr << std::setw(3) << H[i]; std::cerr << "\n";
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