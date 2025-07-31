
#include "worldmap.h"
std::vector<std::vector<int>> create_map(int N, int M,std::vector<int> A, std::vector<int> B) {
    // st2
    int K = 240;
    std::vector<std::vector<int>> o;
    std::vector<std::vector<int>> neigh(N+1);
    for(int i = 0; i < M; i++) {
        neigh[A[i]].push_back(B[i]);
        neigh[B[i]].push_back(A[i]);
    }
    int x = 0;
    std::vector<int> par(N+1);
    
    auto dfs = [&](auto self,int w,int pr=-1) -> void {
        int h = 1;
        for(auto i : neigh[w]) 
        {
            if (i == pr) continue;
            o.emplace_back(K,w);
            self(self,i,w);
        }
        o.emplace_back(K,w);
    };
    dfs(dfs,1);
    K = o.size();
    for(auto& i : o) i.resize(K);
    return o;

}