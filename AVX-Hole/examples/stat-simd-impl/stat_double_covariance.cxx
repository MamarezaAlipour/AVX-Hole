// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <algorithm>
#include <avxhole/stat_simd.hxx>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD Covariance Double Example." << std::endl;

	// Length of sequences
	int n {100};

	// Pseudo-random number generator
	Random_values<int, double> rand(0);

	// Sequences of pseudo-random values
	std::vector<double> x(n);
	std::vector<double> y(n);

	std::generate_n(x.begin(), n, rand);
	std::generate_n(y.begin(), n, rand);

	// Compute covariance
	double m1 = avxhole::covariance_serial(n, x.data(), y.data());
	double m2 = avxhole::covariance_avx2(n, x.data(), y.data());
	double m3 = avxhole::covariance_avx512(n, x.data(), y.data());

	// Display result
	std::cout << "\ncovariance (serial) = " << m1 << "\ncovariance (avx2)   = " << m2
			  << "\ncovariance (avx512) = " << m3 << std::endl;
}