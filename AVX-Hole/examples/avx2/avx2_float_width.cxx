#include <avxhole/simd.hxx>
#include <iostream>

int main() {
	std::cout << "\nSIMD AVX2 Float Width Example." << std::endl;

	// Compute width of SIMD object
	constexpr std::int32_t w = avxhole::simd::avx2_width<std::int32_t, float>();

	// Display result
	std::cout << "\nw = " << w << std::endl; // w = 8
}