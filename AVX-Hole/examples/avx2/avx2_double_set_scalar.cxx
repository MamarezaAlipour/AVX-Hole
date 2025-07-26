
// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX2 Double Set Scalar Example." << std::endl;

	// Scalar value
	double scalar = 3.14;

	// Create SIMD vector with all elements set to scalar value
	auto va = _mm256_set1_pd(scalar);

	// Store result to verify
	std::vector<double> result(4);
	avxhole::simd::avx2_store(result.data(), va);

	// Display result
	std::cout << "\nResult: ";
	for (double val : result) {
		std::cout << val << " ";
	}
	std::cout << std::endl;

	return 0;
}
