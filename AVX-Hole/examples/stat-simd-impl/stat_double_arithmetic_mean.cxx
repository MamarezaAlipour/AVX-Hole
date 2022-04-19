// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <algorithm>
#include <avxhole/stat_simd.hxx>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD Arithmetic Mean Double Example." << std::endl;

	// Length of sequence
	int n {100};

	// Pseudo-random number generator
	Random_values<int, double> rand(0);

	// Sequence of pseudo-random values
	std::vector<double> x(n);

	std::generate_n(x.begin(), n, rand);

	// Compute arithmetic mean
	double m1 = avxhole::arithmetic_mean_serial(n, x.data());
	double m2 = avxhole::arithmetic_mean_avx2(n, x.data());
	double m3 = avxhole::arithmetic_mean_avx512(n, x.data());

	// Display result
	std::cout << "\narithmetic mean (serial) = " << m1 << "\narithmetic mean (avx2)   = " << m2
			  << "\narithmetic mean (avx512) = " << m3 << std::endl;
}