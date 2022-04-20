// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <algorithm>
#include <avxhole/stat_simd.hxx>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD Covariance Float Example." << std::endl;

	// Length of sequences
	int n {100};

	// Pseudo-random number generator
	Random_values<int, float> rand(0);

	// Sequences of pseudo-random values
	std::vector<float> x(n);
	std::vector<float> y(n);

	std::generate_n(x.begin(), n, rand);
	std::generate_n(y.begin(), n, rand);

	// Compute arithmetic mean
	float m1 = avxhole::covariance_serial(n, x.data(), y.data());
	float m2 = avxhole::covariance_avx2(n, x.data(), y.data());
	float m3 = avxhole::covariance_avx512(n, x.data(), y.data());

	// Display result
	std::cout << "\ncovariance (serial) = " << m1 << "\ncovariance (avx2)   = " << m2
			  << "\ncovariance (avx512) = " << m3 << std::endl;
}