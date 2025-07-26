
// Simple test for AVX2 operations
#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>
#include <iostream>
#include <vector>

int main() {
    std::cout << "Simple AVX2 Test" << std::endl;
    
    // Test data
    std::vector<float> a = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    std::vector<float> b = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
    std::vector<float> result(8);
    
    // Load data
    auto va = avxhole::simd::avx2_load(a.data());
    auto vb = avxhole::simd::avx2_load(b.data());
    
    // Add
    auto vc = avxhole::simd::avx2_add(va, vb);
    
    // Store result
    avxhole::simd::avx2_store(result.data(), vc);
    
    // Print result
    avxhole::util::print_vector("Result", result.size(), result.data(), 1, 6);
    
    return 0;
}
