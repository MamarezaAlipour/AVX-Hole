
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
        
        // AVX2 FMA functions
        inline __m256 avx2_fma(const __m256& a, const __m256& b, const __m256& c) {
            return _mm256_fmadd_ps(a, b, c);
        }
        
        inline __m256d avx2_fma(const __m256d& a, const __m256d& b, const __m256d& c) {
            return _mm256_fmadd_pd(a, b, c);
        }
        
        // AVX2 reduce functions
        inline float avx2_reduce(const __m256& vec) {
            __m128 low = _mm256_castps256_ps128(vec);
            __m128 high = _mm256_extractf128_ps(vec, 1);
            __m128 sum = _mm_add_ps(low, high);
            __m128 shuf = _mm_movehdup_ps(sum);
            sum = _mm_add_ps(sum, shuf);
            shuf = _mm_movehl_ps(shuf, sum);
            sum = _mm_add_ss(sum, shuf);
            return _mm_cvtss_f32(sum);
        }
        
        inline double avx2_reduce(const __m256d& vec) {
            __m128d low = _mm256_castpd256_pd128(vec);
            __m128d high = _mm256_extractf128_pd(vec, 1);
            __m128d sum = _mm_add_pd(low, high);
            __m128d shuf = _mm_unpackhi_pd(sum, sum);
            sum = _mm_add_sd(sum, shuf);
            return _mm_cvtsd_f64(sum);
        }
        
        // AVX512 reduce functions
        inline float avx512_reduce(const __m512& vec) {
            return _mm512_reduce_add_ps(vec);
        }
        
        inline double avx512_reduce(const __m512d& vec) {
            return _mm512_reduce_add_pd(vec);
        }
        
        // AVX512 load functions
        inline __m512 avx512_load(const float* data) {
            return _mm512_loadu_ps(data);
        }
        
        inline __m512d avx512_load(const double* data) {
            return _mm512_loadu_pd(data);
        }
        
        // AVX512 store functions
        inline void avx512_store(float* data, __m512 vec) {
            _mm512_storeu_ps(data, vec);
        }
        
        inline void avx512_store(double* data, __m512d vec) {
            _mm512_storeu_pd(data, vec);
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
        
        explicit simd_vector(T scalar) {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                data_ = internal::avx2_float::set_scalar(scalar);
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                data_ = internal::avx2_double::set_scalar(scalar);
            }
#ifdef __AVX512F__
            else if constexpr (std::is_same_v<T, float> && Width == 16) {
                data_ = internal::avx512_float::set_scalar(scalar);
            } else if constexpr (std::is_same_v<T, double> && Width == 8) {
                data_ = internal::avx512_double::set_scalar(scalar);
            }
#endif
        }
        
        explicit simd_vector(const T* data) {
            load(data);
        }
        
        explicit simd_vector(typename internal::simd_traits<T, Width>::register_type reg) : data_(reg) {}
        
        // Basic operations
        simd_vector operator+(const simd_vector& other) const {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                return simd_vector(internal::avx2_float::add(data_, other.data_));
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                return simd_vector(internal::avx2_double::add(data_, other.data_));
            }
        }
        
        simd_vector operator-(const simd_vector& other) const {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                return simd_vector(internal::avx2_float::sub(data_, other.data_));
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                return simd_vector(internal::avx2_double::sub(data_, other.data_));
            }
        }
        
        simd_vector operator*(const simd_vector& other) const {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                return simd_vector(internal::avx2_float::mul(data_, other.data_));
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                return simd_vector(internal::avx2_double::mul(data_, other.data_));
            }
        }
        
        simd_vector operator/(const simd_vector& other) const {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                return simd_vector(internal::avx2_float::div(data_, other.data_));
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                return simd_vector(internal::avx2_double::div(data_, other.data_));
            }
        }
        
        // FMA operations
        simd_vector fma(const simd_vector& b, const simd_vector& c) const {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                return simd_vector(internal::avx2_float::fma(data_, b.data_, c.data_));
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                return simd_vector(internal::avx2_double::fma(data_, b.data_, c.data_));
            }
        }
        
        // Load/Store operations
        void load(const T* data) {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                data_ = internal::avx2_float::load(data);
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                data_ = internal::avx2_double::load(data);
            }
        }
        
        void store(T* data) const {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                internal::avx2_float::store(data, data_);
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                internal::avx2_double::store(data, data_);
            }
        }
        
        // Reduction operations
        T reduce_add() const {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                return internal::avx2_float::reduce_add(data_);
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                return internal::avx2_double::reduce_add(data_);
            }
        }
        
        T reduce_mul() const {
            // Implementation for reduce_mul would go here
            return T{};
        }
        
        // Broadcast operations
        static simd_vector broadcast(T value) {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                return simd_vector(internal::avx2_float::broadcast(value));
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                return simd_vector(internal::avx2_double::broadcast(value));
            }
        }
        
        static simd_vector zero() {
            if constexpr (std::is_same_v<T, float> && Width == 8) {
                return simd_vector(internal::avx2_float::set_zero());
            } else if constexpr (std::is_same_v<T, double> && Width == 4) {
                return simd_vector(internal::avx2_double::set_zero());
            }
        }
        
    private:
        typename internal::simd_traits<T, Width>::register_type data_;
    };
    
    // Type aliases for common SIMD types
    using avx2_float = simd_vector<float, 8>;
    using avx2_double = simd_vector<double, 4>;
    using avx512_float = simd_vector<float, 16>;
    using avx512_double = simd_vector<double, 8>;
    
} // namespace avxhole
