// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <iostream>
#include "test_avx2_float.hxx"
#include "test_avx2_double.hxx"
#include "test_avx512_float.hxx"
#include "test_avx512_double.hxx"

int main() {
	test_avx2_float();
	test_avx2_double();
	test_avx512_float();
	test_avx512_double();

	std::cout << "\nEnd of tests.\n\n\n";
}