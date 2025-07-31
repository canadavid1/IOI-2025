#include "worldmap.h"
#include <iostream>
#include <set>

int main()
{
    int N,M;
    std::cin >> N >> M;
    std::vector<int> A(M),B(M);
    for(int i = 0; i < M; i++) std::cin >> A[i] >> B[i];
    auto o = create_map(N,M,A,B);
    int K = o.size();
    std::set<std::pair<int,int>> neigh;
    for(int i = 0; i < K; i++)
    for(int j = 0; j < K; j++)
    {
        if (i < K-1) neigh.emplace(std::min(o[i][j],o[i+1][j]),std::max(o[i][j],o[i+1][j]));
        if (j < K-1) neigh.emplace(std::min(o[i][j],o[i][j+1]),std::max(o[i][j],o[i][j+1]));
    }
    if (false) {
        for(auto& i : o) {
            for(auto& j : i) std::cout << j << " ";
            std::cout << "\n";
        }
    }
    for(int i = 0; i < M; i++)
    {
        int x = std::min(A[i],B[i]);
        int y = std::max(A[i],B[i]);
        if(!neigh.count({x,y})) {
            std::cerr << x << " and " << y << " do not neighbour\n";
            exit(1);
        }
        neigh.erase({x,y});
    }
    for(auto[x,y] : neigh)
    {
        if (x==y) continue;
        std::cerr << x << " and " << y << " should not neighbour\n";
        exit(2);
    }
    std::cout << "success with K=" << K << "\n";
}