// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX2 Double Fused Multiply-Add Example." << std::endl;

	// Input data
	std::vector<double> a {5.5, 5.5, 5.5, 5.5};
	std::vector<double> b {2.2, 2.2, 2.2, 2.2};
	std::vector<double> c {1.1, 1.1, 1.1, 1.1};

	// Container to store solution
	std::vector<double> d(4);

	// Define SIMD objects using input data
	auto va = avxhole::simd::avx2_load(a.data());
	auto vb = avxhole::simd::avx2_load(b.data());
	auto vc = avxhole::simd::avx2_load(c.data());

	// Compute SIMD operation d = (a * b) + c
	auto vd = avxhole::simd::avx2_fma(va, vb, vc);

	// Transfer data from SIMD object to container
	avxhole::simd::avx2_store(d.data(), vd);

	// Display result
	avxhole::util::print_vector("\nd", d.size(), d.data(), 3, 4);

	// d = [
	//  13.2 13.2 13.2 13.2
	// ]
}