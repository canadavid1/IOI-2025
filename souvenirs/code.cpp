#include "souvenirs.h"


void buy_souvenirs(int N, long long P0) {
    // st2
    for(int i = 1; i < N; i++) {
        auto Pi = P0 - i;
        for(int j = 0; j < i; j++) transaction(Pi); 
    }
}