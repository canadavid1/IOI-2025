#include "obstacles.h"
#include <algorithm>
std::vector<int> T,H,Tinv;
std::vector<int> component;
int N,M;
void initialize(std::vector<int> _T, std::vector<int> _H) {
    // coordinate compress
    N = _T.size();
    M = _H.size();
    std::vector<std::pair<int,int>> seen;seen.reserve(N+M);
    for(int i = 0; i < N; i++) seen.emplace_back(_T[i],~i);
    for(int i = 0; i < M; i++) seen.emplace_back(_H[i],i);
    std::sort(seen.begin(),seen.end());
    T = std::vector<int>(N);
    H = std::vector<int>(M);
    int Ti = 0;
    for(auto [j,i] : seen) {
        if (i < 0) {
            T[~i] = Ti++;
        } else {
            H[i] = Ti;
        }
    }
    // now T is a permutation of range(N), and 0 <= H[i] <= N. Comparison is now T >= H if traversible. 
    // Tinv = std::vector<int>(N);
    // for(int i = 0; i < M; i++) Tinv[T[i]] = i;
    // -------------- (i,j) TRAVERSIBLE IF T[i] >= H[j] ----------------------------------------
    // calculate, for each starting position (0,j), the highest x-coordinate it can reach

    /*
        
        know about the grid: no 2x2 checkerboard as subgrid*
        ie for any two x1,x2 and y1,y2, G(x1,y1) == G(x2,y2) && G(x1,y2) == G(x2,y1) => all equal
        ie G(x1,y2) != G(x1,y1) != G(x2,y1) => G(x1,y1) != G(x2,y2)

        this is necessary and sufficient
        
         021120
        1 X  X
        0 XXXX
        2
    */
    component.reserve(M);
    int s = 0;
    for(int i = 0; i < H.size(); i++) {
        if(H[i] == N) s++;
        component.push_back(s);
    }
}

bool can_reach(int L, int R, int S, int D) {
    // if (L > 0 || R < M-1) return false;
    return component[S] == component[D];
}
