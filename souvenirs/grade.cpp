#include "souvenirs.h"
#include <iostream>

std::vector<long long> P;
std::vector<int> ct;
int query = 0;

std::pair<std::vector<int>, long long> transaction(long long M) {
    std::vector<int> o;
    if (++query >= 5000) {
        std::cerr << "too many queries\n";
        exit(3);
    }
    if (M < *P.rbegin()) {
        std::cerr << "M too small: " << M << "\n";
        exit(2);
    }
    for(int i = 0; i < P.size(); i++)
    {
        if (P[i] <= M) {
            M -= P[i];
            ct[i]++;
            o.push_back(i);
        }
    }
    return {o,M};
}

int main()
{
    int N;
    std::cin >> N;
    P = std::vector<long long>(N);
    ct = std::vector<int>(N,0);
    for(auto& i : P) std::cin >> i;
    buy_souvenirs(N,P[0]);
    for(int i = 0; i < N; i++) if (ct[i] != i) {
        std::cerr << "wrong count of " << i << ": " << ct[i] << "\n";
        exit(1);
    }
    std::cout << "success with " << query << " queries\n";
}