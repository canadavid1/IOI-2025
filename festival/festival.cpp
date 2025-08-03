#include "festival.h"
#include <algorithm>


std::vector<int> max_coupons(int A, std::vector<int> P, std::vector<int> T) {
    std::vector<std::pair<int,int>> coupons;
    for(int i = 0; i < P.size(); i++) coupons.emplace_back(P[i],i);
    std::sort(coupons.begin(),coupons.end());
    std::vector<int> o;
    for(auto[v,i] : coupons) {
        if (v > A) break;
        o.push_back(i);
        A -= v;
    }
    return o;
}
