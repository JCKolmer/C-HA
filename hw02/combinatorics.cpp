#include "combinatorics.h"


uint64_t factorial(uint64_t val) {
    uint64_t a{1};
    uint64_t i = 1;
    while(i < val)
    {
        i++;
        a = a * i;

    }
    return a;
}


uint64_t permutation(uint64_t val, uint64_t val2) {
    uint64_t ergebnis = factorial(val) / factorial(val-val2);
    return ergebnis;
}


uint64_t combination(uint64_t val, uint64_t val2) {
    uint64_t ergebnis = factorial(val) / factorial(val2) * factorial(val-val2);
    return ergebnis;
}
