// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <algorithm>
#include <avxhole/stat_simd.hxx>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD Standard Deviation Double Example." << std::endl;

	// Length of sequence
	int n {100};

	// Pseudo-random number generator
	Random_values<int, double> rand(0);

	// Sequence of pseudo-random values
	std::vector<double> x(n);

	std::generate_n(x.begin(), n, rand);

	// Compute standard deviation
	double m1 = avxhole::standard_deviation_serial(n, x.data());
	double m2 = avxhole::standard_deviation_avx2(n, x.data());
	double m3 = avxhole::standard_deviation_avx512(n, x.data());

	// Display result
	std::cout << "\nstandard deviation (serial) = " << m1 << "\nstandard deviation (avx2)   = " << m2
			  << "\nstandard deviation (avx512) = " << m3 << std::endl;
}