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
#pragma once

#include <span>
#include <numeric>
#include <cmath>

namespace avxhole::stat::impl::serial {
    
    template<typename T>
    T arithmetic_mean(std::span<const T> data) {
        if (data.empty()) return T{0};
        return std::accumulate(data.begin(), data.end(), T{0}) / static_cast<T>(data.size());
    }
    
    template<typename T>
    T variance(std::span<const T> data) {
        if (data.size() < 2) return T{0};
        
        T mean = arithmetic_mean(data);
        T sum_sq_diff = T{0};
        
        for (const auto& value : data) {
            T diff = value - mean;
            sum_sq_diff += diff * diff;
        }
        
        return sum_sq_diff / static_cast<T>(data.size() - 1);
    }
    
    template<typename T>
    T covariance(std::span<const T> x, std::span<const T> y) {
        if (x.size() != y.size() || x.size() < 2) return T{0};
        
        T mean_x = arithmetic_mean(x);
        T mean_y = arithmetic_mean(y);
        T sum = T{0};
        
        for (std::size_t i = 0; i < x.size(); ++i) {
            sum += (x[i] - mean_x) * (y[i] - mean_y);
        }
        
        return sum / static_cast<T>(x.size() - 1);
    }
    
} // namespace avxhole::stat::impl::serial
