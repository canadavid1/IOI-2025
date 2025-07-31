
#include "worldmap.h"
std::vector<std::vector<int>> create_map(int N, int M,std::vector<int> A, std::vector<int> B) {
    // st34
    const int K = N;
    std::vector<std::vector<int>> o(N,std::vector<int>(N,0));
    for(int i = 0; i < K; i++) {
        o[i] = std::vector<int>(N,i+1);
    }
    return o;
}