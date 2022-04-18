// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX512 Float Broadcast Example." << std::endl;

	// Container to store solution
	std::vector<float> a(16);

	// Scalar value
	float s = 5.5;

	// Broadcast scalar value to each element of SIMD object
	auto va = avxhole::simd::avx512_broadcast(&s);

	// Transfer data from SIMD object to container
	avxhole::simd::avx512_store(a.data(), va);

	// Display result
	avxhole::util::print_vector("\na", a.size(), a.data(), 2, 3);

	// a = [
	//  5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5
	// ]
}