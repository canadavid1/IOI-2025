
/*
    4 pixels per connection
    fold over:


    dfs tree: very deep,edges go only upwards (num bounded by #nodes below)

    centroid -> use max height N

    diagonals interesting (almost double the N)

*/
#include <iostream>
#include <cstdlib>
#include "worldmap.h"

std::vector<std::vector<int>> try_solve(int N, int M,std::vector<int> A, std::vector<int> B, int K) {
    std::vector<std::vector<int>> o(K,std::vector<int>(K));
    std::vector<std::vector<int>> neigh(N+1);
    for(int i = 0; i < M; i++) {
        neigh[A[i]].push_back(B[i]);
        neigh[B[i]].push_back(A[i]);
    }
    int x = 0;
    std::vector<int> par(N+1);
    std::vector<int> seen(N+1,0);
    auto outp = [&](int v) {

        for(int i = 0; i < K; i++) if(0 <= x-i && x-i < K) o[i][x-i] = v;
        x++;
    };
    auto dfs = [&](auto self,int w,int pr=-1,int d=1) -> bool {
        if(w == 0) {
            std::cerr << "whaaat\n";
        }
        int h = 1;
        std::vector<int> ex;
        std::vector<int> ot;
        if (seen[w]) return false;
        seen[w] = d;
        for(auto i : neigh[w]) 
        {
            if (i == pr) continue;
            if(seen[i] && seen[i] < d-1)
            {
                ex.push_back(i);
                continue;
            }
            if (seen[i]) continue;
            // o.emplace_back(1,w);
            ot.emplace_back(i);
            // self(self,i,w,d+1);
        }
        bool done_ex = ex.size() == 0;
        auto do_ex = [&](){
            if (done_ex) return;
            done_ex = true;
            while (ex.size()) {
                for(int i = 0; i < K; i++) {
                    if (0 > x-i || x-i >= K) continue;
                    if(ex.size() == 0) ex.push_back(w);
                    o[i][x-i] = ex.back();
                    ex.pop_back();
                }
                x++;
                if (x >= 2*K) {
                    o.clear();
                    return;
                };
                outp(w);
            }
        };
        outp(w);
        for(auto i : ot) {
            // if (x >= K/2) do_ex();
            if (self(self,i,w,d+1)) outp(w);
            if (x >= 2*K) {
                o.clear();
                return false;
            };
        }
        do_ex();
        return true;
        // o.emplace_back(1,w);
        // if (ex.size())
        // {
        //     std::vector<int> a(K,w);
        //     for(int i = 0; i < ex.size(); i++) a[2*i] = ex[i];
        //     o.push_back(std::move(ex));
        //     o.emplace_back(K,w);
        // }
    };
    dfs(dfs,1);
    while(x < 2*K) outp(1);
    return o;
}
std::vector<std::vector<int>> create_map(int N, int M,std::vector<int> A, std::vector<int> B) {
    // st2
    for(int K = N; ; K += N/2) {
        auto o = try_solve(N,M,A,B,K);
        if (o.size()) return o;
    }

}