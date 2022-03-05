// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#ifndef AVXHOLE_TEST_HELPERS_HXX
#define AVXHOLE_TEST_HELPERS_HXX

#include <string_view>
#include <type_traits>
#include <iostream>

//
// Helper functions used throughout

template <class I>
bool compare_sequences(I first1, I last1, I first2) {
	using T = typename I::value_type;

	T eps = std::numeric_limits<T>::epsilon();
	T tol = eps * 10;

	bool flag{ false };	 // chosen to be equivalent to int{0}

	for (; first1 != last1; ++first1, ++first2) {
		T diff = (*first1) - (*first2);

		if (std::abs(diff) > tol)
			flag = true;
	}

	return flag;
}



template <typename I>
void print_sequence(std::string_view str, I first, I last) {
	std::cout << str << ":" << std::endl;

	for (; first != last; ++first)
		std::cout << " " << *first;

	std::cout << std::endl;
}


#endif