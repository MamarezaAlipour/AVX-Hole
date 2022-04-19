// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#ifndef AVXHOLE_STAT_IMPL_SERIAL_HXX
#define AVXHOLE_STAT_IMPL_SERIAL_HXX

#include <avxhole/internal/concepts.hxx>
#include <cmath>

namespace avxhole {

	//----------------------------------------------------------------------------//
	// Declarations

	template <Integer I, Real R>
	inline R arithmetic_mean_serial(I n, R const x[]);

	template <Integer I, Real R>
	inline R variance_serial(I n, R const x[]);

	template <Integer I, Real R>
	inline R standard_deviation_serial(I n, R const x[]);

	template <Integer I, Real R>
	inline R covariance_serial(I n, R const x[], R const y[]);

	template <Integer I, Real R>
	inline R correlation_serial(I n, R const x[], R const y[]);

	//----------------------------------------------------------------------------//
	// Definitions

	// Arithmetic Mean

	template <Integer I, Real R>
	inline R arithmetic_mean_serial(I n, R const x[]) {
		R sum {0.0};

		for (I i {0}; i < n; ++i)
			sum += x[i];

		return sum / n;
	}

	// Variance

	template <Integer I, Real R>
	inline R variance_serial(I n, R const x[]) {
		// Compute the mean of the sequence
		R sum {0.0};

		for (I i {0}; i < n; ++i)
			sum += x[i];

		R mean = sum / n;

		// Compute and return the variance of the sequence
		sum = 0.0;

		for (I i {0}; i < n; ++i) {
			R center = x[i] - mean;
			sum += center * center;
		}

		return sum / (n - 1);
	}

	// Standard Deviation

	template <Integer I, Real R>
	inline R standard_deviation_serial(I n, R const x[]) {
		// Compute the mean of the sequence
		R sum {0.0};

		for (I i {0}; i < n; ++i)
			sum += x[i];

		R mean = sum / n;

		// Compute the variance of the sequence
		sum = 0.0;

		for (I i {0}; i < n; ++i) {
			R center = x[i] - mean;
			sum += center * center;
		}

		R var = sum / (n - 1);

		// Compute and return the standard deviation of the sequence
		return std::sqrt(var);
	}

	// Covariance

	template <Integer I, Real R>
	inline R covariance_serial(I n, R const x[], R const y[]) {
		// Compute the mean of the first sequence
		R sum {0.0};

		for (I i {0}; i < n; ++i)
			sum += x[i];

		R x_mean = sum / n;

		// Compute the mean of the second sequence
		sum = 0.0;

		for (I i {0}; i < n; ++i)
			sum += y[i];

		R y_mean = sum / n;

		// Compute and return the covariance of the two sequences
		sum = 0.0;

		for (I i {0}; i < n; ++i) {
			R x_center = x[i] - x_mean;
			R y_center = y[i] - y_mean;
			sum += x_center * y_center;
		}

		return sum / (n - 1);
	}

	// Correlation

	template <Integer I, Real R>
	inline R correlation_serial(I n, R const x[], R const y[]) {
		// Compute the mean of the first sequence
		R sum {0.0};

		for (I i {0}; i < n; ++i)
			sum += x[i];

		R x_mean = sum / n;

		// Compute the variance of the first sequence
		sum = 0.0;

		for (I i {0}; i < n; ++i) {
			R x_center = x[i] - x_mean;
			sum += x_center * x_center;
		}

		R x_var = sum / (n - 1);

		// Compute the mean of the second sequence
		sum = 0.0;

		for (I i {0}; i < n; ++i)
			sum += y[i];

		R y_mean = sum / n;

		// Compute the variance of the second sequence
		sum = 0.0;

		for (I i {0}; i < n; ++i) {
			R y_center = y[i] - y_mean;
			sum += y_center * y_center;
		}

		R y_var = sum / (n - 1);

		// Compute the standard deviation of the two sequences
		R x_std = std::sqrt(x_var);
		R y_std = std::sqrt(y_var);

		// Compute and return the correlation of the two sequences
		sum = 0.0;

		for (I i {0}; i < n; ++i) {
			R x_center = x[i] - x_mean;
			R y_center = y[i] - y_mean;
			sum += x_center * y_center;
		}

		R cov = sum / (n - 1);
		return cov / (x_std * y_std);
	}

} // namespace avxhole

#endif