
#include <iostream>
#include <vector>
#include <algorithm>
#include <avxhole/simd.hxx>

int main() {
	std::vector<float> a(8);

	float s = 5.5f;

	// Create SIMD vector and broadcast scalar value
	avxhole::avx2_float va = avxhole::avx2_float::broadcast(s);

	// Store result
	va.store(a.data());

	std::cout << "Broadcast " << s << " to 8 elements: ";
	std::for_each(a.begin(), a.end(), [](float f) { std::cout << f << " "; });
	std::cout << std::endl;

	return 0;
}
