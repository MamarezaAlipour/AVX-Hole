// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <algorithm>
#include <avxhole/stat_simd.hxx>
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD Standard Deviation Float Example." << std::endl;

	// Length of sequence
	int n {100};

	// Pseudo-random number generator
	Random_values<int, float> rand(0);

	// Sequence of pseudo-random values
	std::vector<float> x(n);

	std::generate_n(x.begin(), n, rand);

	// Compute arithmetic mean
	float m1 = avxhole::standard_deviation_serial(n, x.data());
	float m2 = avxhole::standard_deviation_avx2(n, x.data());
	float m3 = avxhole::standard_deviation_avx512(n, x.data());

	// Display result
	std::cout << "\nstandard deviation (serial) = " << m1 << "\nstandard deviation (avx2)   = " << m2
			  << "\nstandard deviation (avx512) = " << m3 << std::endl;
}