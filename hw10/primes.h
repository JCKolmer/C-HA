#pragma once

#include <cmath>
#include <algorithm>

// TODO:
// Exercise 2:
// Implement greated common divisor using constexpr, such that it can be evaluated at compile time.
// Your implementation should use variadic templates, to enable calling it
// with any number of arguments, ensure that at least two arguments are provided.
//

template <typename T1>
constexpr T1 gcd( T1 a,  T1 b) 
{ 
    T1 result = std::min(a, b); 
    while (result > 0) { 
        if (a % result == 0 && b % result == 0) { 
            break;
        } 
        result--;
    } 
    return result; 
} 
template <typename T1, typename ... T>
constexpr T1 gcd(T1 var1, T1 var2, const T... args) {
    if (sizeof...(args)>0)
    {
        return gcd(gcd(var1,var2), args...);
    }
    return gcd(var1,var2);
}


// Exercise 3:
// Implement minimum common multiple using constexpr, such that it can be evaluated at compile time.
// As with GCD, your implementation should use variadic templates, to enable calling it
// with arbitrary number of arguments, but at least two
//
template <typename T1>
constexpr T1 mcm(T1 a, T1 b)
{
    if((a==0) & (b==0))
    {
        return 0;
    }
    T1 c = a * b;
    if(c < 0)
    {
        c = -c;
    }
    return c / gcd(a,b);

}
template <typename T1, typename ... T>
constexpr T1 mcm(T1 var1, T1 var2, const T... args) {
    if (sizeof...(args)>0)
    {
        return mcm(mcm(var1,var2), args...);
    }
    return mcm(var1,var2);
}
// Exercise 4:
// Implement power using template metaprogramming. The template struct must be
// called `Power`, and be callable with `Power<base, exponent, modulus>::value`.
// I.e. it needs a compile time evaluation `value`, which holds the result of
// the computation.
// Think about your base cases
template <unsigned base, unsigned exponent, unsigned modulus>
struct Power {
    static constexpr unsigned value = (Power<base, exponent - 1, modulus>::value * base) % modulus;
};

template<unsigned exponent, unsigned modulos>
struct Power<0, exponent, modulos>
{
    static constexpr unsigned value = 0;
};

template<unsigned base, unsigned modulos>
struct Power<base, 0, modulos>
{
    static constexpr unsigned value = 1 % modulos;
};
