#pragma once

#include <array>

// TODO: Implement the Quadruple struct, with the required specialisations
// - The general case should store types and have getters for each called `get_first`, `get_second`,
// etc
// - Implement once specialization if all types are ints. Store them in a publicly accessible
// `std::array`, again provide the getters.
// - Implement once specialization if all types are the same. Store them in a publicly accessible
// `std::array`, again provide the getters.
template <typename T, typename U, typename V, typename W> struct Quadruple {
public:

T get_first() {return first;}
U get_second() {return second;}
V get_third() {return third;}
W get_fourth() {return fourth;}

private:
    T first;
    U second;
    V third;
    W fourth;
};
template <>
struct Quadruple <int, int, int, int> {
public: 

int get_first() {return array1[0]; }
int get_second() {return array1[1]; }
int get_third() {return array1[2]; }
int get_fourth() {return array1[3]; }


private:

std::array<int, 4> array1;
};

template<typename T>
struct  Quadruple <T,T,T,T> {
public:

private:

std::array<T, 4> array2;
};


