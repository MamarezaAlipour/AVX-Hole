// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <algorithm>
#include <avxhole/stat_simd.hxx>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD Correlation Float Example." << std::endl;

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
	float m1 = avxhole::correlation_serial(n, x.data(), y.data());
	float m2 = avxhole::correlation_avx2(n, x.data(), y.data());
	float m3 = avxhole::correlation_avx512(n, x.data(), y.data());

	// Display result
	std::cout << "\ncorrelation (serial) = " << m1 << "\ncorrelation (avx2)   = " << m2
			  << "\ncorrelation (avx512) = " << m3 << std::endl;
}