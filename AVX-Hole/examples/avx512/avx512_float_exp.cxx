
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
        data[i] = static_cast<float>(i) * 0.01f;
    }
    
    // AVX-512 exponential approximation
    auto start = std::chrono::high_resolution_clock::now();
    
    for (std::size_t i = 0; i < size; i += 16) {
        __m512 vec = _mm512_load_ps(&data[i]);
        // Use polynomial approximation for exp
        __m512 one = _mm512_set1_ps(1.0f);
        __m512 result_vec = _mm512_add_ps(one, vec);
        result_vec = _mm512_fmadd_ps(vec, _mm512_mul_ps(vec, _mm512_set1_ps(0.5f)), result_vec);
        _mm512_store_ps(&result[i], result_vec);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "AVX-512 float exp approximation completed in " << duration.count() << " microseconds\n";
    std::cout << "First few results: ";
    for (int i = 0; i < 16; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << "\n";
    
    return 0;
}
