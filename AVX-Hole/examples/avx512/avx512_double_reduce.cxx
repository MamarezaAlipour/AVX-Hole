// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX512 Double Reduce Example." << std::endl;

	// Input data
	std::vector<double> a {1.1, 4.9, 2.3, 3.5, 5.7, 2.8, 0.6, 8.0};

	// Define SIMD object using input data
	auto va = avxhole::simd::avx512_load(a.data());

	// Compute sum of all elements in SIMD object
	double r = avxhole::simd::avx512_reduce(va);

	// Display result
	std::cout << "\nr = " << r << std::endl; // r = 28.9
}