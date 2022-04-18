// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#ifndef AVXHOLE_PRNG_HXX
#define AVXHOLE_PRNG_HXX

#include <avxhole/internal/concepts.hxx>
#include <random>

template <avxhole::Integer I, avxhole::Real R>
class Random_values {

	using Generator = std::mt19937;
	using Distribution = std::normal_distribution<R>;

  public:
	Random_values() = default;
	Random_values(I seed)
		: gen(seed) {}

	R operator()() {
		return dist(gen);
	}

  private:
	Generator gen {std::random_device {}()};
	Distribution dist {0.5, 2.0};
};

#endif
