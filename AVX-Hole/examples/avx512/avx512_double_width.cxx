// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <iostream>

int main() {
	std::cout << "\nSIMD AVX512 Double Width Example." << std::endl;

	// Compute width of SIMD object
	constexpr std::int32_t w = avxhole::simd::avx512_width<std::int32_t, double>();

	// Display result
	std::cout << "\nw = " << w << std::endl; // w = 8
}