
#include "worldmap.h"
std::vector<std::vector<int>> create_map(int N, int M,std::vector<int> A, std::vector<int> B) {
    // st4
    const int K = 240;
    std::vector<std::vector<int>> o(K,std::vector<int>(K,1));
    int x = 0;
    int y = 0;
    for(int i = 0; i < M; i++) {
        o[y][x++] = A[i];
        o[y][x++] = B[i];
        if(++x == K) {
            x = 0;
            y += 2;
        }
    }
    return o;
}