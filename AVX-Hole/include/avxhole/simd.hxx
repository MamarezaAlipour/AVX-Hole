
#pragma once

#include "internal/concepts.hxx"
#include "internal/traits.hxx"
#include "internal/avx2.hxx"
#include "internal/avx512.hxx"

#include <immintrin.h>
#include <type_traits>
#include <concepts>

namespace avxhole {
    
    // Legacy namespace for backward compatibility
    namespace simd {
        // AVX2 load functions
        inline __m256 avx2_load(const float* data) {
            return _mm256_loadu_ps(data);
        }
        
        inline __m256d avx2_load(const double* data) {
            return _mm256_loadu_pd(data);
        }
        
        // AVX2 store functions
        inline void avx2_store(float* data, __m256 vec) {
            _mm256_storeu_ps(data, vec);
        }
        
        inline void avx2_store(double* data, __m256d vec) {
            _mm256_storeu_pd(data, vec);
        }
        
        // AVX2 arithmetic functions
        inline __m256 avx2_add(const __m256& a, const __m256& b) {
            return _mm256_add_ps(a, b);
        }
        
        inline __m256d avx2_add(const __m256d& a, const __m256d& b) {
            return _mm256_add_pd(a, b);
        }
        
        inline __m256 avx2_sub(const __m256& a, const __m256& b) {
            return _mm256_sub_ps(a, b);
        }
        
        inline __m256d avx2_sub(const __m256d& a, const __m256d& b) {
            return _mm256_sub_pd(a, b);
        }
        
        inline __m256 avx2_mul(const __m256& a, const __m256& b) {
            return _mm256_mul_ps(a, b);
        }
        
        inline __m256d avx2_mul(const __m256d& a, const __m256d& b) {
            return _mm256_mul_pd(a, b);
        }
        
        inline __m256 avx2_div(const __m256& a, const __m256& b) {
            return _mm256_div_ps(a, b);
        }
        
        inline __m256d avx2_div(const __m256d& a, const __m256d& b) {
            return _mm256_div_pd(a, b);
        }
    }
    
    // Main SIMD vector wrapper
    template<typename T, std::size_t Width>
    class simd_vector {
    public:
        using value_type = T;
        static constexpr std::size_t width = Width;
        
        // Constructors
        simd_vector() = default;
        explicit simd_vector(T scalar);
        explicit simd_vector(const T* data);
        
        // Basic operations
        simd_vector operator+(const simd_vector& other) const;
        simd_vector operator-(const simd_vector& other) const;
        simd_vector operator*(const simd_vector& other) const;
        simd_vector operator/(const simd_vector& other) const;
        
        // FMA operations
        simd_vector fma(const simd_vector& b, const simd_vector& c) const;
        
        // Load/Store operations
        void load(const T* data);
        void store(T* data) const;
        
        // Reduction operations
        T reduce_add() const;
        T reduce_mul() const;
        
        // Broadcast operations
        static simd_vector broadcast(T value);
        static simd_vector zero();
        
    private:
        typename internal::simd_traits<T, Width>::register_type data_;
    };
    
    // Type aliases for common SIMD types
    using avx2_float = simd_vector<float, 8>;
    using avx2_double = simd_vector<double, 4>;
    using avx512_float = simd_vector<float, 16>;
    using avx512_double = simd_vector<double, 8>;
    
} // namespace avxhole
