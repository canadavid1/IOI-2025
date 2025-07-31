#include "souvenirs.h"
#include <iostream>
/*
    have to query > P0-N for first
    

    N=3:
        query p-1
            only 1:
                know price, ans that-1 twice
            both:
                know sum, ans half (round down)
    query p-1
        only 1:
            know price. Continue
        more than 1 (ct):
            querying with val/ct must work


    if find Plast:
        query doubling the rest every time (start with rest=Plast), Plast+Plast*2**N
        at most one new each time.  
    
    how to find Plast:
        query minimum allowed value every time
        if sum of k numbers are S, query S/k
        
    st3:
        P[i+1] in {Pi-1,Pi-2}

        ans P[i-1]-1
        if more than one: must be P[N-1] == 1


    not adaptive (!)
*/

void buy_souvenirs(int N, long long P0) {
    // st3
    std::vector<long long> P(N,0);
    std::vector<int> ct(N,0);

    P[0] = P0;
    auto test = [&](long long M){
        auto[o,r] = transaction(M);
        for(auto i : o) ct[i]++;
        return std::pair{o,r};
    };
    for(int i = 1; i < N; i++)
    {
        if (P[i]) continue;
        auto[o,r] = test(P[i-1]-1);
        if (o.size() > 1 || r == 1) {
            P[i] = P[i-1]-2;
            if (o.size() > 1) {P[N-1] = 1;}
        }
        else {
            P[i] = P[i-1]-1;
        }
    }
    

    for(int i = 1; i < N; i++)
    {
        if(!P[i] && ct[i] < i) {
            std::cerr << "solver failure\n";
            exit(5);
        }
        while(ct[i] < i) test(P[i]);
    }
    
}