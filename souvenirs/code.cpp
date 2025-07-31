#include "souvenirs.h"
#include <iostream>
#include <tuple>
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

    st5:
        P[i] >= P[i+1] + P[i+2] 
        P[i] <= 2P[i+1]

        2P[i+1] >= P[i] >= P[i+1] + P[i+2]

        P[i] > 2P[i+2] >= P[i+1]

        P[i+1] >= P[i]-P[i+1] >= P[i+2]

        how does this help?
        
        from bottom: P[i+2] => query 2P[i+2]
        this guarantees to get P[i+1] but not P[i]

        again, need to get Plast

        halve each time? yes
        P[i]/2 >= P[i-1]
*/

void buy_souvenirs(int N, long long P0) {
    std::vector<long long> P(N,0);
    std::vector<int> ct(N,0);
    std::vector<std::tuple<std::vector<int>,long long,long long>> hist;
    hist.reserve(5000);
    P[0] = P0;
    auto test = [&](long long M) -> std::pair<std::vector<int>&,long long> {
        auto[o,r] = transaction(M);
        for(auto i : o) ct[i]++;
        hist.emplace_back(std::move(o),r,M);
        return {std::get<0>(hist.back()),r};
    };
    int Pt = P[0]>>((N-1)/2);
    for(int i = 1; i < N; i++)
    {
        Pt = Pt/2;
        // if (P[i]) continue;
        auto[o,r] = test(Pt);
        std::cerr << "query " << Pt << " to get r=" << r << " and o =";
        for(auto e : o) std::cerr << " " << e;
        std::cerr << "\n";
        if (o.size() == 1) {
            P[o[0]] = Pt-r;
            if (o[0] == N-1) break;
            if (o[0] == N-2) {
                Pt = 2*(P[N-2]-1);
            }
        }
    }
    std::cerr << "here\n";
    int hi = hist.size()-1;
    for(int i = N-1; i >= 1; i--) {
        if (P[i]) continue;
        long long s = 0;
        while (hi >= 0 && std::get<0>(hist[hi]).front() > i) hi--;
        std::vector<int> o;
        long long r,M;
        if (hi >= 0) std::tie(o,r,M) = hist[hi];
        if (hi < 0 || o[0] != i) {
            std::tie(o,r) = test(P[i+1]*2);
            M = P[i+1]*2;
        }
        bool contains = 0;
        for(auto j : o) {
            s += P[j];
        }
        P[i] = M - r - s;
    }
    std::cerr << "P[i] =";
    for(auto i : P) std::cerr << " " << i;
    std::cerr << "\n";
    

    for(int i = 1; i < N; i++)
    {
        if(!P[i] && ct[i] < i) {
            std::cerr << "solver failure\n";
            exit(5);
        }
        while(ct[i] < i) test(P[i]);
    }
    
}