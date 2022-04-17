// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX2 Float Set Scalar Example." << std::endl;

	// Container to store solution
	std::vector<float> a(8);

	// Define SIMD object using scalar value
	auto va = avxhole::simd::avx2_set_scalar(5.5f);

	// Transfer data from SIMD object to container
	avxhole::simd::avx2_store(a.data(), va);

	// Display result
	avxhole::util::print_vector("\na", a.size(), a.data(), 2, 3);

	// a = [
	//  5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5
	// ]
}