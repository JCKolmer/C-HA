#include "combinatorics.h"


uint64_t factorial(uint64_t val) {
    if(val==0)
    {
        return 1;
    }
    uint64_t factorial{1};
   for(uint64_t i = 1; i <= val; ++i) {
            factorial *= i;
        }
    return factorial;
}


uint64_t permutation(uint64_t val, uint64_t val2) {
    if(val2>val)
    {
        return 0;
    }
    uint64_t ergebnis = factorial(val) / factorial(val-val2);
    return ergebnis;
}


uint64_t combination(uint64_t val, uint64_t val2) {
    if(val2>val)
    {
        return 0;
    }
    uint64_t ergebnis = factorial(val) / factorial(val2) * factorial(val-val2);
    return ergebnis;
}
