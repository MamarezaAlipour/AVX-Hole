#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <random>

namespace avxhole {
namespace util {

template<typename T>
void print_vector(const std::string& name, size_t size, const T* data, 
                  int precision = 6, int width = 8) {
    std::cout << name << " = [" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        if (i % 4 == 0 && i > 0) std::cout << std::endl;
        std::cout << " " << std::setw(width) << std::setprecision(precision) 
                  << std::fixed << data[i];
    }
    std::cout << std::endl << "]" << std::endl;
}

} // namespace util
} // namespace avxhole