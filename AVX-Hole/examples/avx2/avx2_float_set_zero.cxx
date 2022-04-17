// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX2 Float Set Zero Example." << std::endl;

	// Container to store solution
	std::vector<float> a(8);

	// Define SIMD object of zeros
	auto va = avxhole::simd::avx2_set_zero<float>();

	// Transfer data from SIMD object to container
	avxhole::simd::avx2_store(a.data(), va);

	// Display result
	avxhole::util::print_vector("\na", a.size(), a.data(), 1, 1);

	// a = [
	//  0 0 0 0 0 0 0 0
	// ]
}