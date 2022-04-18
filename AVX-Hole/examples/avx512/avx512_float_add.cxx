// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX512 Float Addition Example." << std::endl;

	// Input data
	std::vector<float> a {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,
						  5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5};
	std::vector<float> b {2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2,
						  2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2};

	// Container to store solution
	std::vector<float> c(16);

	// Define SIMD objects using input data
	auto va = avxhole::simd::avx512_load(a.data());
	auto vb = avxhole::simd::avx512_load(b.data());

	// Compute SIMD operation c = a + b
	auto vc = avxhole::simd::avx512_add(va, vb);

	// Transfer data from SIMD object to container
	avxhole::simd::avx512_store(c.data(), vc);

	// Display result
	avxhole::util::print_vector("\nc", c.size(), c.data(), 2, 3);

	// c = [
	//  7.7 7.7 7.7 7.7 7.7 7.7 7.7 7.7 7.7 7.7 7.7 7.7 7.7 7.7 7.7 7.7
	// ]
}