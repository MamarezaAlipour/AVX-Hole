// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX2 Double Reduce Example." << std::endl;

	// Input data
	std::vector<double> a {1.1, 4.9, 2.3, 3.5};

	// Define SIMD object using input data
	auto va = avxhole::simd::avx2_load(a.data());

	// Compute sum of all elements in SIMD object
	double r = avxhole::simd::avx2_reduce(va);

	// Display result
	std::cout << "\nr = " << r << std::endl; // r = 11.8
}