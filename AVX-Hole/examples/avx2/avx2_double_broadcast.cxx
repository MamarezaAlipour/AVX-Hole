
#include <iostream>
#include <vector>
#include <algorithm>
#include <avxhole/simd.hxx>

int main() {
	std::vector<double> a(4);

	double s = 5.5;

	// Create SIMD vector and broadcast scalar value
	avxhole::avx2_double va = avxhole::avx2_double::broadcast(s);

	// Store result
	va.store(a.data());

	std::cout << "Broadcast " << s << " to 4 elements: ";
	std::for_each(a.begin(), a.end(), [](double d) { std::cout << d << " "; });
	std::cout << std::endl;

	return 0;
}
