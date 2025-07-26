
#include "../../include/avxhole/simd.hxx"
#include <iostream>
#include <vector>
#include <chrono>

constexpr int N = 256;

void matrix_multiply_avx2(const float* A, const float* B, float* C) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; j += 8) {
            __m256 sum = _mm256_setzero_ps();
            
            for (int k = 0; k < N; ++k) {
                __m256 a = _mm256_broadcast_ss(&A[i * N + k]);
                __m256 b = _mm256_load_ps(&B[k * N + j]);
                sum = _mm256_fmadd_ps(a, b, sum);
            }
            
            _mm256_store_ps(&C[i * N + j], sum);
        }
    }
}

int main() {
    std::vector<float> A(N * N, 1.0f);
    std::vector<float> B(N * N, 2.0f);
    std::vector<float> C(N * N, 0.0f);
    
    auto start = std::chrono::high_resolution_clock::now();
    matrix_multiply_avx2(A.data(), B.data(), C.data());
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "AVX2 matrix multiplication (" << N << "x" << N << ") completed in " 
              << duration.count() << " milliseconds\n";
    std::cout << "Result C[0][0] = " << C[0] << "\n";
    
    return 0;
}
