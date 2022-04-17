#include <iostream>
#include <avxhole/simd.hxx>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX2 Float Reduce Example." << std::endl;

	// Input data
	std::vector<float> a {1.1, 4.9, 2.3, 3.5, 5.7, 2.8, 0.6, 8.0};

	// Define SIMD object using input data
	auto va = avxhole::simd::avx2_load(a.data());

	// Compute sum of all elements in SIMD object
	float r = avxhole::simd::avx2_reduce(va);

	// Display result
	std::cout << "\nr = " << r << std::endl; // r = 28.9
}