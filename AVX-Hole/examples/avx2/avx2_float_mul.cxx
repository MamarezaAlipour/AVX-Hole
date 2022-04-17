// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX2 Float Multiplication Example." << std::endl;

	// Input data
	std::vector<float> a {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5};
	std::vector<float> b {2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2};

	// Container to store solution
	std::vector<float> c(8);

	// Define SIMD objects using input data
	auto va = avxhole::simd::avx2_load(a.data());
	auto vb = avxhole::simd::avx2_load(b.data());

	// Compute SIMD operation c = a * b
	auto vc = avxhole::simd::avx2_mul(va, vb);

	// Transfer data from SIMD object to container
	avxhole::simd::avx2_store(c.data(), vc);

	// Display result
	avxhole::util::print_vector("\nc", c.size(), c.data(), 3, 4);

	// c = [
	//  12.1 12.1 12.1 12.1 12.1 12.1 12.1 12.1
	// ]
}