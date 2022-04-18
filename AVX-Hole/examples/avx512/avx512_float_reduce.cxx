// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX512 Float Reduce Example." << std::endl;

	// Input data
	std::vector<float> a {1.1, 4.9, 2.3, 3.5, 5.7, 2.8, 0.6, 8.0,
						  6.2, 2.5, 4.3, 0.7, 4.8, 3.0, 1.8, 2.1};

	// Define SIMD object using input data
	auto va = avxhole::simd::avx512_load(a.data());

	// Compute sum of all elements in SIMD object
	float r = avxhole::simd::avx512_reduce(va);

	// Display result
	std::cout << "\nr = " << r << std::endl; // r = 54.3
}