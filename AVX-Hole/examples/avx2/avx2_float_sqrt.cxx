
#include "../../include/avxhole/simd.hxx"
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

int main() {
    constexpr std::size_t size = 1024;
    std::vector<float> data(size);
    std::vector<float> result(size);
    
    // Initialize with test data
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = static_cast<float>(i + 1);
    }
    
    // AVX2 sqrt approximation using Newton-Raphson
    auto start = std::chrono::high_resolution_clock::now();
    
    for (std::size_t i = 0; i < size; i += 8) {
        __m256 vec = _mm256_load_ps(&data[i]);
        __m256 sqrt_vec = _mm256_sqrt_ps(vec);
        _mm256_store_ps(&result[i], sqrt_vec);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "AVX2 float sqrt completed in " << duration.count() << " microseconds\n";
    std::cout << "First few results: ";
    for (int i = 0; i < 8; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << "\n";
    
    return 0;
}
