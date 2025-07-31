
#include "triples.h"

#include <iostream>


int main()
{
    int t;
    std::cin >> t;
    if(t == 1) {
    int N;
    std::cin >> N;
    std::vector<int> H(N);
    for(auto& i : H) std::cin >> i;
    std::cout << count_triples(H) << "\n";
    }
}