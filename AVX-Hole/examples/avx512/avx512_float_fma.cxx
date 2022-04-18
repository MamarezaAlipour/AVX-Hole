// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX512 Float Fused Multiply-Add Example." << std::endl;

	// Input data
	std::vector<float> a {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,
						  5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5};
	std::vector<float> b {2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2,
						  2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2};
	std::vector<float> c {1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1,
						  1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1};

	// Container to store solution
	std::vector<float> d(16);

	// Define SIMD objects using input data
	auto va = avxhole::simd::avx512_load(a.data());
	auto vb = avxhole::simd::avx512_load(b.data());
	auto vc = avxhole::simd::avx512_load(c.data());

	// Compute SIMD operation d = (a * b) + c
	auto vd = avxhole::simd::avx512_fma(va, vb, vc);

	// Transfer data from SIMD object to container
	avxhole::simd::avx512_store(d.data(), vd);

	// Display result
	avxhole::util::print_vector("\nd", d.size(), d.data(), 3, 4);

	// d = [
	//  13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2
	// ]
}