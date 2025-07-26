
#ifdef __AVX512F__
#include <iostream>
#include <vector>
#include <algorithm>
#include <avxhole/simd.hxx>

int main() {
	std::vector<double> a(8);

	double s = 5.5;

	// Create SIMD vector and broadcast scalar value
	avxhole::avx512_double va = avxhole::avx512_double::broadcast(s);

	// Store result
	va.store(a.data());

	std::cout << "Broadcast " << s << " to 8 elements: ";
	std::for_each(a.begin(), a.end(), [](double d) { std::cout << d << " "; });
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
