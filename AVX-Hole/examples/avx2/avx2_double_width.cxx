// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <iostream>
#include <avxhole/simd.hxx>

int main() {
	std::cout << "\nSIMD AVX2 Double Width Example." << std::endl;

	// Compute width of SIMD object
	constexpr std::int32_t w = avxhole::simd::avx2_width<std::int32_t, double>();

	// Display result
	std::cout << "\nw = " << w << std::endl;  // w = 4
}