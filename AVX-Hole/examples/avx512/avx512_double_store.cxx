// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX512 Double Store Example." << std::endl;

	// Input data
	std::vector<double> a {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5};

	// Container to store solution
	std::vector<double> b(8);

	// Define SIMD object using input data
	auto va = avxhole::simd::avx512_load(a.data());

	// Transfer data from SIMD object to container
	avxhole::simd::avx512_store(b.data(), va);

	// Display result
	avxhole::util::print_vector("\nb", b.size(), b.data(), 2, 3);

	// b = [
	//  5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5
	// ]
}