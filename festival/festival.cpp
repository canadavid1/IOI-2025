#include "festival.h"
#include <algorithm>
#include <set>

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
    // buy all bought coupons with T=2 before T=1
    std::vector<int> best;
    for(int T2 = 0; T2 <= coupons[2].size(); T2++) {
        long long X = A;
        std::vector<int> o;
        // buy T2 coupons of T=2
        for(int i = 0; i < T2; i++) {
            auto[v,idx] = coupons[2][i];
            if (X < v) break;
            o.push_back(idx);
            X -= v;
            X *= 2;
            if (X >= N * 1000000) return got_infinity(o,N);
        }
        for(auto[v,idx] : coupons[1]) {
            if (X < v) break;
            o.push_back(idx);
            X -= v;
        }
        if (o.size() > best.size()) best = std::move(o);
    }
    end:;
    return best;
}
