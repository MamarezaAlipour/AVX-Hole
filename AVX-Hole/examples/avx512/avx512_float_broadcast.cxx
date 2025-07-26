
#ifdef __AVX512F__
#include <iostream>
#include <vector>
#include <algorithm>
#include <avxhole/simd.hxx>

int main() {
	std::vector<float> a(16);

	float s = 5.5f;

	// Create SIMD vector and broadcast scalar value
	avxhole::avx512_float va = avxhole::avx512_float::broadcast(s);

	// Store result
	va.store(a.data());

	std::cout << "Broadcast " << s << " to 16 elements: ";
	std::for_each(a.begin(), a.end(), [](float f) { std::cout << f << " "; });
	std::cout << std::endl;

	return 0;
}
#else
#include <iostream>
int main() {
	std::cout << "AVX-512 not supported on this system" << std::endl;
	return 0;
}
#endif
