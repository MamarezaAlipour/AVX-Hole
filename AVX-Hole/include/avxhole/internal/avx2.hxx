#pragma once

#include "concepts.hxx"
#include "traits.hxx"
#include <immintrin.h>

namespace avxhole::internal {

    // AVX2 Float operations
    namespace avx2_float {

        inline __m256 set_zero() {
            return _mm256_setzero_ps();
        }

        inline __m256 set_scalar(float value) {
            return _mm256_set1_ps(value);
        }

        inline __m256 load(const float* data) {
            return _mm256_load_ps(data);
        }

        inline void store(float* data, __m256 vec) {
            _mm256_store_ps(data, vec);
        }

        inline __m256 add(__m256 a, __m256 b) {
            return _mm256_add_ps(a, b);
        }

        inline __m256 sub(__m256 a, __m256 b) {
            return _mm256_sub_ps(a, b);
        }

        inline __m256 mul(__m256 a, __m256 b) {
            return _mm256_mul_ps(a, b);
        }

        inline __m256 div(__m256 a, __m256 b) {
            return _mm256_div_ps(a, b);
        }

        inline __m256 fma(__m256 a, __m256 b, __m256 c) {
            return _mm256_fmadd_ps(a, b, c);
        }

        inline __m256 broadcast(float value) {
            return _mm256_broadcast_ss(&value);
        }

        inline float reduce_add(__m256 vec) {
            __m128 low = _mm256_castps256_ps128(vec);
            __m128 high = _mm256_extractf128_ps(vec, 1);
            __m128 sum = _mm_add_ps(low, high);
            sum = _mm_hadd_ps(sum, sum);
            sum = _mm_hadd_ps(sum, sum);
            return _mm_cvtss_f32(sum);
        }

    } // namespace avx2_float

    // AVX2 Double operations
    namespace avx2_double {

        inline __m256d set_zero() {
            return _mm256_setzero_pd();
        }

        inline __m256d set_scalar(double value) {
            return _mm256_set1_pd(value);
        }

        inline __m256d load(const double* data) {
            return _mm256_load_pd(data);
        }

        inline void store(double* data, __m256d vec) {
            _mm256_store_pd(data, vec);
        }

        inline __m256d add(__m256d a, __m256d b) {
            return _mm256_add_pd(a, b);
        }

        inline __m256d sub(__m256d a, __m256d b) {
            return _mm256_sub_pd(a, b);
        }

        inline __m256d mul(__m256d a, __m256d b) {
            return _mm256_mul_pd(a, b);
        }

        inline __m256d div(__m256d a, __m256d b) {
            return _mm256_div_pd(a, b);
        }

        inline __m256d fma(__m256d a, __m256d b, __m256d c) {
            return _mm256_fmadd_pd(a, b, c);
        }

        inline __m256d broadcast(double value) {
            return _mm256_broadcast_sd(&value);
        }

        inline double reduce_add(__m256d vec) {
            __m128d low = _mm256_castpd256_pd128(vec);
            __m128d high = _mm256_extractf128_pd(vec, 1);
            __m128d sum = _mm_add_pd(low, high);
            sum = _mm_hadd_pd(sum, sum);
            return _mm_cvtsd_f64(sum);
        }

    } // namespace avx2_double

} // namespace avxhole::internal