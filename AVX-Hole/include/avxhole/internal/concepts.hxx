// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#ifndef AVXHOLE_CONCEPTS_HXX
#define AVXHOLE_CONCEPTS_HXX

#include <avxhole/internal/traits.hxx>

namespace avxhole {
	// concept Integer
	template <class T>
	concept Integer = avxhole::is_integer_v<T>;

	// concept Real
	template <class T>
	concept Real = avxhole::is_real_v<T>;
} // namespace avxhole

#endif // !AVXHOLE_CONCEPTS_HXX
