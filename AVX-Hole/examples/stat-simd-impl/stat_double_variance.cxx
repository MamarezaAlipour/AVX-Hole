// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <algorithm>
#include <avxhole/stat_simd.hxx>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD Variance Double Example." << std::endl;

	// Length of sequence
	int n {100};

	// Pseudo-random number generator
	Random_values<int, double> rand(0);

	// Sequence of pseudo-random values
	std::vector<double> x(n);

	std::generate_n(x.begin(), n, rand);

	// Compute variance
	double m1 = avxhole::variance_serial(n, x.data());
	double m2 = avxhole::variance_avx2(n, x.data());
	double m3 = avxhole::variance_avx512(n, x.data());

	// Display result
	std::cout << "\nvariance (serial) = " << m1 << "\nvariance (avx2)   = " << m2 << "\nvariance (avx512) = " << m3
			  << std::endl;
}