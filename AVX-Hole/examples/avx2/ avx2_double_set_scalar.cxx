// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <iostream>
#include <vector>
#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>


int main() {
	std::cout << "\nSIMD AVX2 Double Set Scalar Example." << std::endl;

	// Container to store solution
	std::vector<double> a(4);

	// Define SIMD object using scalar value
	auto va = avxhole::simd::avx2_set_scalar(5.5);

	// Transfer data from SIMD object to container
	avxhole::simd::avx2_store(a.data(), va);

	// Display result
	avxhole::util::print_vector("\na", a.size(), a.data(), 2, 3);

	// a = [
	//  5.5 5.5 5.5 5.5
	// ]
}