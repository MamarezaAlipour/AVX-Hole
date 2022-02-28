// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#ifndef AVXHOLE_AVX512_HXX
#define AVXHOLE_AVX512_HXX

#include <cstdint>
#include <immintrin.h>
#include <avxhole/internal/concepts.hxx>

namespace avxhole::simd {
	// Type aliases
	using v512f = __m512;
	using v512d = __m512d;

	// Declarations
	template <Integer I, Real R> // Helper class declaration
	struct avx512_width;

	template <Real R>
	inline auto avx512_set_zero();

	inline v512f avx512_set_scalar(float a);
	inline v512d avx512_set_scalar(double a);

	inline v512f avx512_broadcast(float const* addr);
	inline v512d avx512_broadcast(double const* addr);

	inline v512f avx512_load(float const* addr);
	inline v512d avx512_load(double const* addr);

	inline void avx512_store(float* addr, v512f a);
	inline void avx512_store(double* addr, v512d a);

	inline v512f avx512_add(v512f a, v512f b);
	inline v512d avx512_add(v512d a, v512d b);

	inline v512f avx512_sub(v512f a, v512f b);
	inline v512d avx512_sub(v512d a, v512d b);

	inline v512f avx512_mul(v512f a, v512f b);
	inline v512d avx512_mul(v512d a, v512d b);

	inline v512f avx512_div(v512f a, v512f b);
	inline v512d avx512_div(v512d a, v512d b);

	inline v512f avx512_fma(v512f a, v512f b, v512f c);
	inline v512d avx512_fma(v512d a, v512d b, v512d c);

	inline float avx512_reduce(v512f a);
	inline double avx512_reduce(v512d a);

	// Helper classes
	// Specializations for avx512_width

	template <Integer I>
	struct avx512_width<I, float> {

		using value_type = I;
		static constexpr value_type value{ 16 };

		constexpr operator value_type() const noexcept { return value; }
	};

	template <Integer I>
	struct avx512_width<I, double> {

		using value_type = I;
		static constexpr value_type value{ 8 };

		constexpr operator value_type() const noexcept { return value; }
	};

	namespace detail {

		template <class Real> // <Real R>
		struct simd_mm512_setzero {
			static auto mm512_setzero();
		};

		template <>
		struct simd_mm512_setzero<float> {
			static auto mm512_setzero() { return _mm512_setzero_ps(); }
		};

		template <>
		struct simd_mm512_setzero<double> {
			static auto mm512_setzero() { return _mm512_setzero_pd(); }
		};

	} //! namespace detail

	// Definitions


	// constexpr auto
	// avx2_width<I, R>();


	template <Real R>
	inline auto avx512_set_zero() { return detail::simd_mm512_setzero<R>::mm512_setzero(); }

	inline v512f avx512_set_scalar(float a) { return _mm512_set1_ps(a); }
	inline v512d avx512_set_scalar(double a) { return _mm512_set1_pd(a); }

	inline v512f avx512_broadcast(float const* addr) {
		__m128 a = _mm_broadcast_ss(addr);
		return _mm512_broadcastss_ps(a);
	}

	inline v512d avx512_broadcast(double const* addr) {
		__m128d a = _mm_load1_pd(addr);
		return _mm512_broadcastsd_pd(a);
	}

	inline v512f avx512_load(float const* addr) { return _mm512_loadu_ps(addr); }
	inline v512d avx512_load(double const* addr) { return _mm512_loadu_pd(addr); }

	inline void avx512_store(float* addr, v512f a) { _mm512_storeu_ps(addr, a); }
	inline void avx512_store(double* addr, v512d a) { _mm512_storeu_pd(addr, a); }

	inline v512f avx512_add(v512f a, v512f b) { return _mm512_add_ps(a, b); }
	inline v512d avx512_add(v512d a, v512d b) { return _mm512_add_pd(a, b); }

	inline v512f avx512_sub(v512f a, v512f b) { return _mm512_sub_ps(a, b); }
	inline v512d avx512_sub(v512d a, v512d b) { return _mm512_sub_pd(a, b); }

	inline v512f avx512_mul(v512f a, v512f b) { return _mm512_mul_ps(a, b); }
	inline v512d avx512_mul(v512d a, v512d b) { return _mm512_mul_pd(a, b); }

	inline v512f avx512_div(v512f a, v512f b) { return _mm512_div_ps(a, b); }
	inline v512d avx512_div(v512d a, v512d b) { return _mm512_div_pd(a, b); }

	inline v512f avx512_fma(v512f a, v512f b, v512f c) { return _mm512_fmadd_ps(a, b, c); }
	inline v512d avx512_fma(v512d a, v512d b, v512d c) { return _mm512_fmadd_pd(a, b, c); }

	inline float avx512_reduce(v512f a) { return _mm512_reduce_add_ps(a); }
	inline double avx512_reduce(v512d a) { return _mm512_reduce_add_pd(a); }
}

#endif // !AVXHOLE_AVX512_HXX
