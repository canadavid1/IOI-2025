#include "triples.h"
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <iomanip>
std::set<std::tuple<int,int,int>> seen;
inline bool works(int i,int j, int k,const std::vector<int>& H) {
    int p[3] = {i,j,k};
    std::sort(p,p+3);
    i = p[0]; j = p[1]; k = p[2];
    if(0 > i || i >= j || j >= k || k >= H.size()) return false;
    if (j - i == H[k] && k - j == H[i]) return false; // avoid double-counting
    if(seen.count({i,j,k})) return false;
    int d[3] = {j-i,k-j,k-i};
    int h[3] = {H[i],H[j],H[k]};
    std::sort(d,d+3);
    std::sort(h,h+3);
    if (d[0] == h[0] && d[1] == h[1] && d[2] == h[2]) {
        // std::cerr << i << " " << j << " " << k << "\n";
        seen.emplace(i,j,k);
        return true;
    }
    return false;
} 
// using comb = std::map<int,int>;
struct comb {
    std::unordered_map<int,int> a;
    long long operator*(const comb& b) const {
        if (a.size() > b.a.size()) return b * *this;
        long long o = 0;
        for(auto[i,v] : a) {
            if(b.a.count(i)) o += (long long)v * b.a.at(i);
        }
        return o;
    }
    void insert(int v) {
        a[v]++;
    }
    void remove(int v) {
        if (!--a[v]) {a.erase(v);}
    }
};
long long count_triples(std::vector<int> H) {
    std::cerr << "count_triples(...)\n";
    /*
        given a starting point i:
        either next point at j=i+H[i], implies third point at i+H[j] or j+H[j]  !! easy
            j = i+H[i]  
        or two points j,k=j+H[i] such that H[j] = j-i and H[k] = k-i            !! okish, separable
                                        j-H[j] = i and k-H[k] = i        these are in total N values, so amortized iteration
                                        (where k=j+H[i])
        or two points j,k=j+H[i] such that H[k] = j-i and H[j] = k-i            !! hard
                                        H[k] = k-H[i]-i
                                        k-H[k] = i+H[i]  
                                        j-H[j] = i-H[i]  [j = k-H[i]]
                                        i+H[i] could alias !! -> note: want this high for part II
                                        H[i] <= 10 makes at most 10 aliases
                                        H non-decreasing also alleviates
        refactoring: if any of the three points (WLOG i) have a distance to one of the others that is H[i], then easy - 
            only two options for j (i ± H[i]) and then four(?) for k: i ± H[j] and j ± H[j]
        else "cycle" 
            i
        Hk Hj
        j Hi  k
        
        WLOG i < j < k
        // Hj = Hk + Hi
        j - i = Hk
        k - j = Hi
        k - i = Hj
        i Hk j Hi k
        Hj - Hk = k - j = Hi
        j + Hj = k + Hk
        Hj - Hi = j - i = Hk
        j - Hi = i - Hi
        Hk + Hi = k - i
        i + Hi = k - Hk
        j + Hj = k + Hk
        j - Hi = i - Hi
        i + Hi = k - Hk
        1 2 3 4
        1 _ 3 2
        0 _ 0 -2
                H x-Hx x+Hx
        i = 1   1 0    2 
        j = 3   3 0    6 -> find two with resp x-Hx = 0 and x+Hx = 6 st i+Hi = k-Hk
        k = 4   2 2    6
        left: map x-Hx => some struct representing x+Hx poss
        right: map x+Hx => some struct representing x-Hx poss
        struct must allow efficient dot product (map and iterate over smallest?)
        
        
    */
    const int N = H.size();
    long long ct = 0;
    std::vector<int> XmH(N);
    std::vector<int> XpH(N);
    for(int x = 0; x < N; x++) {
        XmH[x] = x - H[x];
        XpH[x] = x + H[x];
    }
    std::unordered_map<int,comb> left,right;
    for(int i = 0; i < N; i++) right[XpH[i]].insert(XmH[i]);
    for(int j = 0; j < N; j++) {
        right[XpH[j]].remove(XmH[j]);
        ct += left[XmH[j]]  *  right[XpH[j]];
        left[XmH[j]].insert(XpH[j]);
    }
    std::cerr << "pre-trivial: " << ct << "\n";
    for(int i = 0; i < N; i++) {
        for(int j : {i+H[i],i-H[i]}) {
            if (j < 0 || j >= N) continue;
            for(int k : {i+H[j],i-H[j],j+H[j],j-H[j]}) 
                ct += works(i,j,k,H);
        }
    }
    
    // for(int i = 0; i < N; i++) std::cerr << std::setw(3) << i; std::cerr << "\n";
    // for(int i = 0; i < N; i++) std::cerr << std::setw(3) << H[i]; std::cerr << "\n";
    // for(int i = 0; i < N; i++) std::cerr << std::setw(3) << XmH[i]; std::cerr << "\n";
    // for(int i = 0; i < N; i++) std::cerr << std::setw(3) << XpH[i]; std::cerr << "\n";
    // for(auto[i,j,k] : seen) {
    //     for(int _ = 0; _ < i; _++) std::cerr << "   ";
    //     std::cerr << std::setw(3) << i;
    //     for(int _ = i+1; _ < j; _++) std::cerr << "   ";
    //     std::cerr << std::setw(3) << j;
    //     for(int _ = j+1; _ < k; _++) std::cerr << "   ";
    //     std::cerr << std::setw(3) << k << "\n";
    // }
    std::cerr << " = " << ct << "\n";
    return ct;
}

std::vector<int> construct_range(int M, int K) {
    return {};
}