// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <iostream>
#include <avxhole/internal/concepts.hxx>


template <avxhole::Real R>
R foo(R x, R y) { return x * y + 5; }


template <avxhole::Integer I>
I bar(I x, I y) { return x + y * 5; }


int main() {
	avxhole::Real auto r1 = foo(1., 2.);
	avxhole::Real auto r2 = foo(1.1, 2.1);

	avxhole::Integer auto r3 = bar(1, 2);

	// avxhole::Real auto r4 = foo(1, 2);		 // ERROR!
	// avxhole::Integer auto r5 = bar(1., 2.);	 // ERROR!

	std::cout << "\nr1 = " << r1  // = 7
			  << "\nr2 = " << r2  // = 7.31
			  << "\nr3 = " << r3  // = 11
			  << std::endl;
}