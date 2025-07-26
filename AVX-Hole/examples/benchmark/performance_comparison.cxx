
#include "../../include/avxhole/simd.hxx"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>

template<typename Func>
double benchmark(Func&& func, int iterations = 1000) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        func();
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count() / iterations;
}

int main() {
    constexpr std::size_t size = 10000;
    std::vector<float> a(size), b(size), result(size);
    
    // Initialize with random data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(1.0f, 100.0f);
    
    for (std::size_t i = 0; i < size; ++i) {
        a[i] = dis(gen);
        b[i] = dis(gen);
    }
    
    // Scalar version
    auto scalar_add = [&]() {
        for (std::size_t i = 0; i < size; ++i) {
            result[i] = a[i] + b[i];
        }
    };
    
    // AVX2 version
    auto avx2_add = [&]() {
        for (std::size_t i = 0; i < size; i += 8) {
            __m256 va = _mm256_load_ps(&a[i]);
            __m256 vb = _mm256_load_ps(&b[i]);
            __m256 vr = _mm256_add_ps(va, vb);
            _mm256_store_ps(&result[i], vr);
        }
    };
    
    // AVX-512 version (if available)
    auto avx512_add = [&]() {
        for (std::size_t i = 0; i < size; i += 16) {
            __m512 va = _mm512_load_ps(&a[i]);
            __m512 vb = _mm512_load_ps(&b[i]);
            __m512 vr = _mm512_add_ps(va, vb);
            _mm512_store_ps(&result[i], vr);
        }
    };
    
    std::cout << "Performance Comparison (Average time per operation):\n";
    std::cout << "Scalar ADD: " << benchmark(scalar_add) << " ms\n";
    std::cout << "AVX2 ADD:   " << benchmark(avx2_add) << " ms\n";
    
    #ifdef __AVX512F__
    std::cout << "AVX512 ADD: " << benchmark(avx512_add) << " ms\n";
    #endif
    
    return 0;
}
