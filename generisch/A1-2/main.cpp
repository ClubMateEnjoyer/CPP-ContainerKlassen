#include <iostream>
#include <typeinfo>

#include "vec.h"
#include "test12.h"

int main() {

    std::cout << "Start testing" << std::endl;

    test_vec<float, 3>();
    test_vec<double, 5>();
    test_vec<int, 2>();
    test_vec<long, 10>();
    test_vec<double, 1>();
    test_vec<int, 0>();


    std::cout << "--- all tests passed ---" << std::endl;
    return 0;
}