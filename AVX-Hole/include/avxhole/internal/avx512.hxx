#pragma once

#include "concepts.hxx"
#include "traits.hxx"
#include <immintrin.h>

namespace avxhole::internal {

    // AVX-512 Float operations
    namespace avx512_float {

        inline __m512 set_zero() {
            return _mm512_setzero_ps();
        }

        inline __m512 set_scalar(float value) {
            return _mm512_set1_ps(value);
        }

        inline __m512 load(const float* data) {
            return _mm512_load_ps(data);
        }

        inline void store(float* data, __m512 vec) {
            _mm512_store_ps(data, vec);
        }

        inline __m512 add(__m512 a, __m512 b) {
            return _mm512_add_ps(a, b);
        }

        inline __m512 sub(__m512 a, __m512 b) {
            return _mm512_sub_ps(a, b);
        }

        inline __m512 mul(__m512 a, __m512 b) {
            return _mm512_mul_ps(a, b);
        }

        inline __m512 div(__m512 a, __m512 b) {
            return _mm512_div_ps(a, b);
        }

        inline __m512 fma(__m512 a, __m512 b, __m512 c) {
            return _mm512_fmadd_ps(a, b, c);
        }

        inline __m512 broadcast(float value) {
            return _mm512_set1_ps(value);
        }

        inline float reduce_add(__m512 vec) {
            return _mm512_reduce_add_ps(vec);
        }

    } // namespace avx512_float

    // AVX-512 Double operations
    namespace avx512_double {

        inline __m512d set_zero() {
            return _mm512_setzero_pd();
        }

        inline __m512d set_scalar(double value) {
            return _mm512_set1_pd(value);
        }

        inline __m512d load(const double* data) {
            return _mm512_load_pd(data);
        }

        inline void store(double* data, __m512d vec) {
            _mm512_store_pd(data, vec);
        }

        inline __m512d add(__m512d a, __m512d b) {
            return _mm512_add_pd(a, b);
        }

        inline __m512d sub(__m512d a, __m512d b) {
            return _mm512_sub_pd(a, b);
        }

        inline __m512d mul(__m512d a, __m512d b) {
            return _mm512_mul_pd(a, b);
        }

        inline __m512d div(__m512d a, __m512d b) {
            return _mm512_div_pd(a, b);
        }

        inline __m512d fma(__m512d a, __m512d b, __m512d c) {
            return _mm512_fmadd_pd(a, b, c);
        }

        inline __m512d broadcast(double value) {
            return _mm512_set1_pd(value);
        }

        inline double reduce_add(__m512d vec) {
            return _mm512_reduce_add_pd(vec);
        }

    } // namespace avx512_double

} // namespace avxhole::internal