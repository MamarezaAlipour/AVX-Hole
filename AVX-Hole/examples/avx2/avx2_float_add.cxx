// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>

int main() {
	std::cout << "\nSIMD AVX2 Float Addition Example." << std::endl;

	// Input data
	std::vector<float> a {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5};
	std::vector<float> b {2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2};

	// Container to store solution
	std::vector<float> c(8);

	// Define SIMD objects using input data
	auto va = avxhole::simd::avx2_load(a.data());
	auto vb = avxhole::simd::avx2_load(b.data());

	// Compute SIMD operation c = a + b
	auto cv = avxhole::simd::avx2_add(va, vb);

	// Transfer data from SIMD object to container
	avxhole::simd::avx2_store(c.data(), cv);

	// Display result
	avxhole::util::print_vector("\nc", c.size(), c.data(), 2, 3);

	// c = [
	//  7.7 7.7 7.7 7.7 7.7 7.7 7.7 7.7
	// ]
}
#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>
#include <array>

int main() {
    std::cout << "=== AVX2 Float Addition Example ===" << std::endl;
    
    // Create input vectors
    std::array<float, 8> a = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    std::array<float, 8> b = {8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    std::array<float, 8> c;
    
    std::cout << "Input vectors:" << std::endl;
    avxhole::util::print_vector("a", a.size(), a.data(), 1, 8);
    avxhole::util::print_vector("b", b.size(), b.data(), 1, 8);
    
    // Load vectors using AVX2
    auto va = avxhole::simd::avx2_load(a.data());
    auto vb = avxhole::simd::avx2_load(b.data());
    
    // Perform addition
    auto cv = avxhole::simd::avx2_add(va, vb);
    
    // Store result
    avxhole::simd::avx2_store(c.data(), cv);
    
    // Print result
    avxhole::util::print_vector("c = a + b", c.size(), c.data(), 1, 8);
    
    // Verify result
    bool correct = true;
    for (size_t i = 0; i < 8; ++i) {
        if (std::abs(c[i] - (a[i] + b[i])) > 1e-6f) {
            correct = false;
            break;
        }
    }
    
    std::cout << "\nResult: " << (correct ? "PASSED" : "FAILED") << std::endl;
    
    return correct ? 0 : 1;
}
