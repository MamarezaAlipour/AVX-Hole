// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#ifndef AVXHOLE_STAT_IMPL_AVX2_HXX
#define AVXHOLE_STAT_IMPL_AVX2_HXX

#include <avxhole/simd.hxx>
#include <cmath>

namespace avxhole {

	//----------------------------------------------------------------------------//
	// Declarations

	template <Integer I, Real R>
	inline R arithmetic_mean_avx2(I n, R const x[]);

	template <Integer I, Real R>
	inline R variance_avx2(I n, R const x[]);

	template <Integer I, Real R>
	inline R standard_deviation_avx2(I n, R const x[]);

	template <Integer I, Real R>
	inline R covariance_avx2(I n, R const x[], R const y[]);

	template <Integer I, Real R>
	inline R correlation_avx2(I n, R const x[], R const y[]);

	//----------------------------------------------------------------------------//
	// Definitions

	// Arithmetic Mean

	template <Integer I, Real R>
	inline R arithmetic_mean_avx2(I n, R const x[]) {
		I constexpr w = avxhole::simd::avx2_width<I, R>();
		I m = n % w;

		R sum {0.0};

		for (I i {0}; i < m; ++i)
			sum += x[i];

		if (n < m)
			return sum / n;

		auto vsum = avxhole::simd::avx2_set_zero<R>();

		for (I i {m}; i < n; i += w) {
			auto vx = avxhole::simd::avx2_load(&x[i]);
			vsum = avxhole::simd::avx2_add(vsum, vx);
		}

		sum += avxhole::simd::avx2_reduce(vsum);
		return sum / n;
	}

	// Variance

	template <Integer I, Real R>
	inline R variance_avx2(I n, R const x[]) {
		// Compute the mean of the sequence
		I constexpr w = avxhole::simd::avx2_width<I, R>();
		I m = n % w;

		R sum {0.0};

		for (I i {0}; i < m; ++i)
			sum += x[i];

		if (n >= m) {
			auto vsum = avxhole::simd::avx2_set_zero<R>();

			for (I i {m}; i < n; i += w) {
				auto vx = avxhole::simd::avx2_load(&x[i]);
				vsum = avxhole::simd::avx2_add(vsum, vx);
			}

			sum = sum + avxhole::simd::avx2_reduce(vsum);
		}

		R mean = sum / n;

		// Compute and return the variance of the sequence
		sum = 0.0;

		for (I i {0}; i < m; ++i) {
			R center = x[i] - mean;
			sum += center * center;
		}

		if (n >= m) {
			auto vmean = avxhole::simd::avx2_set_scalar(mean);
			auto vsum = avxhole::simd::avx2_set_zero<R>();

			for (I i {m}; i < n; i += w) {
				auto vx = avxhole::simd::avx2_load(&x[i]);
				auto vcenter = avxhole::simd::avx2_sub(vx, vmean);
				vsum = avxhole::simd::avx2_fma(vcenter, vcenter, vsum);
			}

			sum += avxhole::simd::avx2_reduce(vsum);
		}

		return sum / (n - 1);
	}

	// Standard Deviation

	template <Integer I, Real R>
	inline R standard_deviation_avx2(I n, R const x[]) {
		// Compute the mean of the sequence
		I constexpr w = avxhole::simd::avx2_width<I, R>();
		I m = n % w;

		R sum {0.0};

		for (I i {0}; i < m; ++i)
			sum += x[i];

		if (n >= m) {
			auto vsum = avxhole::simd::avx2_set_zero<R>();

			for (I i {m}; i < n; i += w) {
				auto vx = avxhole::simd::avx2_load(&x[i]);
				vsum = avxhole::simd::avx2_add(vsum, vx);
			}

			sum += avxhole::simd::avx2_reduce(vsum);
		}

		R mean = sum / n;

		// Compute the variance of the sequence
		sum = 0.0;

		for (I i {0}; i < m; ++i) {
			R center = x[i] - mean;
			sum += center * center;
		}

		if (n >= m) {
			auto vmean = avxhole::simd::avx2_set_scalar(mean);
			auto vsum = avxhole::simd::avx2_set_zero<R>();

			for (I i {m}; i < n; i += w) {
				auto vx = avxhole::simd::avx2_load(&x[i]);
				auto vcenter = avxhole::simd::avx2_sub(vx, vmean);
				vsum = avxhole::simd::avx2_fma(vcenter, vcenter, vsum);
			}

			sum += avxhole::simd::avx2_reduce(vsum);
		}

		R var = sum / (n - 1);

		// Compute and return the standard deviation of the sequence
		return std::sqrt(var);
	}

	// Covariance

	template <Integer I, Real R>
	inline R covariance_avx2(I n, R const x[], R const y[]) {
		// Compute the mean of the two sequences
		I constexpr w = avxhole::simd::avx2_width<I, R>();
		I m = n % w;

		R sum1 {0.0};
		R sum2 {0.0};

		for (I i {0}; i < m; ++i) {
			sum1 += x[i];
			sum2 += y[i];
		}

		if (n >= m) {
			auto vsum1 = avxhole::simd::avx2_set_zero<R>();
			auto vsum2 = avxhole::simd::avx2_set_zero<R>();

			for (I i {m}; i < n; i += w) {
				auto vx = avxhole::simd::avx2_load(&x[i]);
				vsum1 = avxhole::simd::avx2_add(vsum1, vx);
				auto vy = avxhole::simd::avx2_load(&y[i]);
				vsum2 = avxhole::simd::avx2_add(vsum2, vy);
			}

			sum1 = sum1 + avxhole::simd::avx2_reduce(vsum1);
			sum2 = sum2 + avxhole::simd::avx2_reduce(vsum2);
		}

		R x_mean = sum1 / n;
		R y_mean = sum2 / n;

		// Compute and return the covariance of the two sequences
		sum1 = 0.0;

		for (I i {0}; i < m; ++i) {
			R x_center = x[i] - x_mean;
			R y_center = y[i] - y_mean;
			sum1 += x_center * y_center;
		}

		if (n >= m) {
			auto vx_mean = avxhole::simd::avx2_set_scalar(x_mean);
			auto vy_mean = avxhole::simd::avx2_set_scalar(y_mean);
			auto vsum = avxhole::simd::avx2_set_zero<R>();

			for (I i {m}; i < n; i += w) {
				auto vx = avxhole::simd::avx2_load(&x[i]);
				auto vx_center = avxhole::simd::avx2_sub(vx, vx_mean);
				auto vy = avxhole::simd::avx2_load(&y[i]);
				auto vy_center = avxhole::simd::avx2_sub(vy, vy_mean);
				vsum = avxhole::simd::avx2_fma(vx_center, vy_center, vsum);
			}

			sum1 = sum1 + avxhole::simd::avx2_reduce(vsum);
		}

		return sum1 / (n - 1);
	}

	// Correlation

	template <Integer I, Real R>
	inline R correlation_avx2(I n, R const x[], R const y[]) {
		// Compute the mean of the two sequences
		I constexpr w = avxhole::simd::avx2_width<I, R>();
		I m = n % w;

		R sum1 {0.0};
		R sum2 {0.0};

		for (I i {0}; i < m; ++i) {
			sum1 += x[i];
			sum2 += y[i];
		}

		if (n >= m) {
			auto vsum1 = avxhole::simd::avx2_set_zero<R>();
			auto vsum2 = avxhole::simd::avx2_set_zero<R>();

			for (I i {m}; i < n; i += w) {
				auto vx = avxhole::simd::avx2_load(&x[i]);
				vsum1 = avxhole::simd::avx2_add(vsum1, vx);
				auto vy = avxhole::simd::avx2_load(&y[i]);
				vsum2 = avxhole::simd::avx2_add(vsum2, vy);
			}

			sum1 = sum1 + avxhole::simd::avx2_reduce(vsum1);
			sum2 = sum2 + avxhole::simd::avx2_reduce(vsum2);
		}

		R x_mean = sum1 / n;
		R y_mean = sum2 / n;

		// Compute the variance of the two sequences
		sum1 = 0.0;
		sum2 = 0.0;

		for (I i {0}; i < m; ++i) {
			R x_center = x[i] - x_mean;
			sum1 += x_center * x_center;
			R y_center = y[i] - y_mean;
			sum2 += y_center * y_center;
		}

		if (n >= m) {
			auto vx_mean = avxhole::simd::avx2_set_scalar(x_mean);
			auto vsum1 = avxhole::simd::avx2_set_zero<R>();
			auto vy_mean = avxhole::simd::avx2_set_scalar(y_mean);
			auto vsum2 = avxhole::simd::avx2_set_zero<R>();

			for (I i {m}; i < n; i += w) {
				auto vx = avxhole::simd::avx2_load(&x[i]);
				auto vx_center = avxhole::simd::avx2_sub(vx, vx_mean);
				vsum1 = avxhole::simd::avx2_fma(vx_center, vx_center, vsum1);
				auto vy = avxhole::simd::avx2_load(&y[i]);
				auto vy_center = avxhole::simd::avx2_sub(vy, vy_mean);
				vsum2 = avxhole::simd::avx2_fma(vy_center, vy_center, vsum2);
			}

			sum1 += avxhole::simd::avx2_reduce(vsum1);
			sum2 += avxhole::simd::avx2_reduce(vsum2);
		}

		R x_var = sum1 / (n - 1);
		R y_var = sum2 / (n - 1);

		// Compute the standard deviation of the two sequences
		R x_std = std::sqrt(x_var);
		R y_std = std::sqrt(y_var);

		// Compute and return the correlation of the two sequences
		sum1 = 0.0;

		for (I i {0}; i < m; ++i) {
			R x_center = x[i] - x_mean;
			R y_center = y[i] - y_mean;
			sum1 += x_center * y_center;
		}

		if (n >= m) {
			auto vx_mean = avxhole::simd::avx2_set_scalar(x_mean);
			auto vy_mean = avxhole::simd::avx2_set_scalar(y_mean);
			auto vsum = avxhole::simd::avx2_set_zero<R>();

			for (I i {m}; i < n; i += w) {
				auto vx = avxhole::simd::avx2_load(&x[i]);
				auto vx_center = avxhole::simd::avx2_sub(vx, vx_mean);
				auto vy = avxhole::simd::avx2_load(&y[i]);
				auto vy_center = avxhole::simd::avx2_sub(vy, vy_mean);
				vsum = avxhole::simd::avx2_fma(vx_center, vy_center, vsum);
			}

			sum1 = sum1 + avxhole::simd::avx2_reduce(vsum);
		}

		R cov = sum1 / (n - 1);
		return cov / (x_std * y_std);
	}

} // namespace avxhole

#endif