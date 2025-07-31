#include "triples.h"
#include <algorithm>
#include <set>
#include <map>
#include <iostream>
inline bool works(int i,int j, int k,const std::vector<int>& H) {
    if( i >= j || j >= k || k >= H.size()) return false;
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

long long count_triples(std::vector<int> H) {
    std::cerr << "count_triples(...)\n";
    /*
        given a starting point i:
        either next point at j=i+H[i], implies third point at i+H[j] or j+H[j]  !! easy
        or two points j,k=j+H[i] such that H[j] = j-i and H[k] = k-i            !! okish, separable
                                           j-H[j] = i and k-H[k] = i        these are in total N values, so amortized iteration
                                           (where k=j+H[i])

        or two points j,k=j+H[i] such that H[k] = j-i and H[j] = k-i            !! hard
                                           H[k] = k-H[i]-i
                                           k-H[k] = i+H[i]  
                                           j-H[j] = i-H[i]  [j = k-H[i]]


                                           i+H[i] could alias !!
                                           H[i] <= 10 makes at most 10 aliases
                                           H non-decreasing also alleviates
                                        
    */
    const int N = H.size();
    long long ct = 0;
    std::vector<int> HmI(N);
    for(int i = 0; i < N; i++) HmI[i] = i-H[i];
    std::vector<int> next_eq_HmI(N);
    std::map<int,int> prev;
    for(int i = N-1; i >= 0; i--) {
        next_eq_HmI[i] = prev[HmI[i]];
        prev[HmI[i]] = i;
    }
    for(int i = 0; i < N-2; i++) {
        int Hi = H[i];
        {
            // easy case
            int j = i+Hi;
            for(auto k : {i+H[j],j+H[j],j-H[j]}) {
                ct += works(i,j,k,H);
                ct += works(i,k,j,H);
            }
        }
        {
            // medium case k = j+H[i], H[j] = j-i, H[k] = k-i
            // ie j-H[j] = i, k-H[k] = i
            for(int j = prev[i]; j != 0; j = next_eq_HmI[j]) {
                int k = j + Hi;
                ct += works(i,j,k,H);
            }
        }
        {
            // hard case k = j+H[i], H[k] = j-i, H[j] = k-i
            //                k-H[k] = i+H[i]  
            //                j-H[j] = i-H[i]  [j = k-H[i]]
            for(int k = prev[i+Hi]; k != 0; k = next_eq_HmI[k]) {
                int j = k - Hi;
                ct += works(i,j,k,H);
            }
        }
    }
    std::cerr << " = " << ct << "\n";
    return ct;
}



std::vector<int> construct_range(int M, int K) {
    return {};
}