#include "souvenirs.h"
/*
    have to query > P0-N for first
    

    N=3:
        query p-1
            only 1:
                know price, ans that-1 twice
            both:
                know sum, ans half (round down)
*/

void buy_souvenirs(int N, long long P0) {
    std::vector<long long> P(N,-1);
    std::vector<int> ct(N,0);

    P[0] = P0;
    // auto test = [&](long long M){
    //     auto[o,r] = transaction(M);
    //     for(auto i : o) ct[i]++;
    //     return std::pair{o,r};
    // };
    auto[o,r] = transaction(P0-1);
    if (o.size() == 1) {
        int P1 = P0-1-r;
        transaction(P1-1);
        transaction(P1-1);
    }
    else {
        int P12 = P0-1-r;
        transaction(P12/2);
    }
    
}