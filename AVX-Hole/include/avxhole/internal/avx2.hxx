// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#ifndef AVXHOLE_AVX2_HXX
#define AVXHOLE_AVX2_HXX

#include <cstdint>
#include <immintrin.h>
#include <avxhole/internal/concepts.hxx>

namespace avxhole::simd {
	// Type aliases
	using v256f = __m256;
	using v256d = __m256d;

	// Declerations
	template <Integer I, Real R> // Helper class decl
	struct avx2_width;

	template <Real R>
	inline auto avx2_set_zero();

	inline v256f avx2_set_scalar(float a);
	inline v256d avx2_set_scalar(double a);

	inline v256f avx2_broadcast(float const* addr);
	inline v256d avx2_broadcast(double const* addr);

	inline v256f avx2_load(float const* addr);
	inline v256d avx2_load(double const* addr);

	inline void avx2_store(float* addr, v256f a);
	inline void avx2_store(double* addr, v256d a);

	inline v256f avx2_add(v256f a, v256f b);
	inline v256d avx2_add(v256d a, v256d b);

	inline v256f avx2_sub(v256f a, v256f b);
	inline v256d avx2_sub(v256d a, v256d b);

	inline v256f avx2_mul(v256f a, v256f b);
	inline v256d avx2_mul(v256d a, v256d b);

	inline v256f avx2_div(v256f a, v256f b);
	inline v256d avx2_div(v256d a, v256d b);

	inline v256f avx2_fma(v256f a, v256f b, v256f c);
	inline v256d avx2_fma(v256d a, v256d b, v256d c);

	inline float avx2_reduce(v256f a);
	inline double avx2_reduce(v256d a);


	// Helper classes
	// Specializations for avx2_width

	template <Integer I>
	struct avx2_width<I, float> {
		using value_type = I;
		static constexpr value_type value{ 8 };

		constexpr operator value_type() const noexcept { return value; }
	};

	template <Integer I>
	struct avx2_width<I, double> {
		using value_type = I;
		static constexpr value_type value{ 4 };

		constexpr operator value_type() const noexcept { return value; }
	};

	// Helper class for avx2_set_zero
	namespace detail {
		template <Real R>
		struct simd_mm256_setzero {
			static auto mm256_setzero();
		};

		template <>
		struct simd_mm256_setzero<float> {
			static auto mm256_setzero() { return _mm256_setzero_ps(); };
		};

		template <>
		struct simd_mm256_setzero<double> {
			static auto mm256_setzero() { return _mm256_setzero_pd(); }
		};
	}

	template <Real R>
	inline auto avx2_set_zero() { return detail::simd_mm256_setzero<R>::mm256_setzero(); }

	inline v256f avx2_set_scalar(float a) { return _mm256_set1_ps(a); }
	inline v256d avx2_set_scalar(double a) { return _mm256_set1_pd(a); }

	inline v256f avx2_broadcast(float const* addr) { return _mm256_broadcast_ss(addr); }
	inline v256d avx2_broadcast(double const* addr) { return _mm256_broadcast_sd(addr); }

	inline v256f avx2_load(float const* addr) { return _mm256_loadu_ps(addr); }
	inline v256d avx2_load(double const* addr) { return _mm256_loadu_pd(addr); }

	inline void avx2_store(float* addr, v256f a) { _mm256_storeu_ps(addr, a); }
	inline void avx2_store(double* addr, v256d a) { _mm256_storeu_pd(addr, a); }

	inline v256f avx2_add(v256f a, v256f b) { return _mm256_add_ps(a, b); }
	inline v256d avx2_add(v256d a, v256d b) { return _mm256_add_pd(a, b); }

	inline v256f avx2_sub(v256f a, v256f b) { return _mm256_sub_ps(a, b); }
	inline v256d avx2_sub(v256d a, v256d b) { return _mm256_sub_pd(a, b); }

	inline v256f avx2_mul(v256f a, v256f b) { return _mm256_mul_ps(a, b); }
	inline v256d avx2_mul(v256d a, v256d b) { return _mm256_mul_pd(a, b); }

	inline v256f avx2_div(v256f a, v256f b) { return _mm256_div_ps(a, b); }
	inline v256d avx2_div(v256d a, v256d b) { return _mm256_div_pd(a, b); }

	inline v256f avx2_fma(v256f a, v256f b, v256f c) { return _mm256_fmadd_ps(a, b, c); }
	inline v256d avx2_fma(v256d a, v256d b, v256d c) { return _mm256_fmadd_pd(a, b, c); }

	inline float avx2_reduce(v256f a) {
		__m128 high128 = _mm256_extractf128_ps(a, 1);
		__m128 low128 = _mm256_castps256_ps128(a);
		__m128 sum128 = _mm_add_ps(low128, high128);

		__m128 low64 = sum128;
		__m128 high64 = _mm_movehl_ps(sum128, sum128);
		__m128 sum64 = _mm_add_ps(low64, high64);

		__m128 low = sum64;
		__m128 high = _mm_shuffle_ps(sum64, sum64, 1);
		__m128 sum = _mm_add_ss(low, high);

		return _mm_cvtss_f32(sum);
	}

	inline double avx2_reduce(v256d a) {
		__m128d high128 = _mm256_extractf128_pd(a, 1);
		__m128d low128 = _mm256_castpd256_pd128(a);
		__m128d sum128 = _mm_add_pd(low128, high128);

		__m128d high64 = _mm_unpackhi_pd(sum128, sum128);
		__m128d low64 = _mm_add_sd(sum128, high64);

		return _mm_cvtsd_f64(low64);
	}
}

#endif // !AVXHOLE_AVX2_HXX
