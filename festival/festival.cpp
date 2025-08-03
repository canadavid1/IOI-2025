#include "festival.h"
#include <algorithm>
#include <set>
#include <map>
#include <iostream>
std::vector<int> got_infinity(std::vector<int> o,int N) {
    // if X >= N*max(P) then can do all rest
    std::set<int> seen;
    for(auto e : o) seen.insert(e);
    for(int i = 0; i < N; i++) if (!seen.count(i)) o.push_back(i);
    return o;
}

std::vector<int> max_coupons(int A, std::vector<int> P, std::vector<int> T) {
    // st2/3
    long long N = P.size();
    std::vector<std::pair<int,int>> coupons[5];
    for(int i = 0; i < N; i++) coupons[T[i]].emplace_back(P[i],i);
    for(auto& i : coupons) std::sort(i.begin(),i.end());
    std::map<long long,int> num_T1_coupons;
    long long s = 0;
    for(int i = 0; i < coupons[1].size(); i++) {
        num_T1_coupons[s] = i;
        s += coupons[1][i].first;
    }
    num_T1_coupons[s] = coupons[1].size();
    // for(auto[k,v]: num_T1_coupons) std::cerr << k << "->" << v << "\n";

    // buy all bought coupons with T=2 before T=1
    // num total, num T2
    std::pair<int,int> best = {0,0};
    long long X = A;
    std::vector<int> o;
    for(int T2 = 0; T2 <= coupons[2].size(); T2++) {
        // buy T2 coupons of T=2
        if (T2 > 0) {
            auto[v,i] = coupons[2][T2-1];
            if (X < v) break;
            o.push_back(i);
            X -= v;
            X *= 2;
            if (X > N*1000*1000*100) return got_infinity(o,N);
        }
        int T1 = (--num_T1_coupons.upper_bound(X))->second;
        best = std::max(best,{T1+T2,T2});
    }
    int T2 = best.second;
    int T1 = best.first-T2;
    o.clear();
    for(int i = 0; i < T2; i++) o.push_back(coupons[2][i].second);
    for(int i = 0; i < T1; i++) o.push_back(coupons[1][i].second);
    return o;
}
