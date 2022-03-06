// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <iostream>
#include <vector>
#include <avxhole/simd.hxx>
#include "test_helpers.hxx"
#include "test_avx2_float.hxx"


int test_avx2_float() {
	std::cout << "\ntest_avx2_float()" << std::endl;

	int fail{ 0 };

	fail += test_avx2_float_width();
	fail += test_avx2_float_set_zero_and_store();
	fail += test_avx2_float_set_scalar();
	fail += test_avx2_float_broadcast();
	fail += test_avx2_float_load();
	fail += test_avx2_float_add();
	fail += test_avx2_float_sub();
	fail += test_avx2_float_mul();
	fail += test_avx2_float_div();
	fail += test_avx2_float_fma();
	fail += test_avx2_float_reduce();

	if (fail == 0)
		std::cout << "test_avx2_float()    passed with zero errors." << std::endl;
	else
		std::cout << "\ntest_avx2_float()    had " << fail << " errors." << std::endl;

	return fail;
}


int test_avx2_float_width() {
	constexpr std::int32_t r = avxhole::simd::avx2_width<std::int32_t, float>();
	std::int32_t soln{ 8 };

	if (r != soln) {
		std::cout << "\nERROR! test_avx2_float_width()"
				  << "\nr    = " << r
				  << "\nsoln = " << soln << std::endl;
		return 1;
	}
	else
		return 0;
}


int test_avx2_float_set_zero_and_store() {
	std::vector<float> a(8);
	std::vector<float> soln(8, 0.0);

	auto va = avxhole::simd::avx2_set_zero<float>();

	avxhole::simd::avx2_store(a.data(), va);

	bool r = compare_sequences(a.begin(), a.end(), soln.begin());

	if (r == true) {
		std::cout << "\nERROR! test_avx2_float_set_zero_and_store()" << std::endl;
		print_sequence("a", a.begin(), a.end());
		print_sequence("soln", soln.begin(), soln.end());
		return 1;
	}
	else
		return 0;
}


int test_avx2_float_set_scalar() {
	std::vector<float> a(8);
	std::vector<float> soln(8, 5.5);

	auto va = avxhole::simd::avx2_set_scalar(5.5f);

	avxhole::simd::avx2_store(a.data(), va);

	bool r = compare_sequences(a.begin(), a.end(), soln.begin());

	if (r == true) {
		std::cout << "\nERROR! test_avx2_float_set_scalar()" << std::endl;
		print_sequence("a", a.begin(), a.end());
		print_sequence("soln", soln.begin(), soln.end());
		return 1;
	}
	else
		return 0;
}


int test_avx2_float_broadcast() {
	std::vector<float> a(8);
	std::vector<float> soln(8, 5.5);
	float s{ 5.5 };

	auto va = avxhole::simd::avx2_broadcast(&s);

	avxhole::simd::avx2_store(a.data(), va);

	bool r = compare_sequences(a.begin(), a.end(), soln.begin());

	if (r == true) {
		std::cout << "\nERROR! test_avx2_float_broadcast()" << std::endl;
		print_sequence("a", a.begin(), a.end());
		print_sequence("soln", soln.begin(), soln.end());
		return 1;
	}
	else
		return 0;
}


int test_avx2_float_load() {
	std::vector<float> a(8, 5.5);
	std::vector<float> b(8);
	std::vector<float> soln(8, 5.5);

	auto va = avxhole::simd::avx2_load(a.data());

	avxhole::simd::avx2_store(b.data(), va);

	bool r = compare_sequences(b.begin(), b.end(), soln.begin());

	if (r == true) {
		std::cout << "\nERROR! test_avx2_float_load()" << std::endl;
		print_sequence("b", b.begin(), b.end());
		print_sequence("soln", soln.begin(), soln.end());
		return 1;
	}
	else
		return 0;
}


int test_avx2_float_add() {
	std::vector<float> a(8, 5.5);
	std::vector<float> b(8, 2.2);
	std::vector<float> c(8);
	std::vector<float> soln(8, 7.7);

	auto va = avxhole::simd::avx2_load(a.data());
	auto vb = avxhole::simd::avx2_load(b.data());

	auto vc = avxhole::simd::avx2_add(va, vb);

	avxhole::simd::avx2_store(c.data(), vc);

	bool r = compare_sequences(c.begin(), c.end(), soln.begin());

	if (r == true) {
		std::cout << "\nERROR! test_avx2_float_add()" << std::endl;
		print_sequence("c", c.begin(), c.end());
		print_sequence("soln", soln.begin(), soln.end());
		return 1;
	}
	else
		return 0;
}


int test_avx2_float_sub() {
	std::vector<float> a(8, 5.5);
	std::vector<float> b(8, 2.2);
	std::vector<float> c(8);
	std::vector<float> soln(8, 3.3);

	auto va = avxhole::simd::avx2_load(a.data());
	auto vb = avxhole::simd::avx2_load(b.data());

	auto vc = avxhole::simd::avx2_sub(va, vb);

	avxhole::simd::avx2_store(c.data(), vc);

	bool r = compare_sequences(c.begin(), c.end(), soln.begin());

	if (r == true) {
		std::cout << "\nERROR! test_avx2_float_sub()" << std::endl;
		print_sequence("c", c.begin(), c.end());
		print_sequence("soln", soln.begin(), soln.end());
		return 1;
	}
	else
		return 0;
}


int test_avx2_float_mul() {
	std::vector<float> a(8, 5.5);
	std::vector<float> b(8, 2.2);
	std::vector<float> c(8);
	std::vector<float> soln(8, 12.1);

	auto va = avxhole::simd::avx2_load(a.data());
	auto vb = avxhole::simd::avx2_load(b.data());

	auto vc = avxhole::simd::avx2_mul(va, vb);

	avxhole::simd::avx2_store(c.data(), vc);

	bool r = compare_sequences(c.begin(), c.end(), soln.begin());

	if (r == true) {
		std::cout << "\nERROR! test_avx2_float_mul()" << std::endl;
		print_sequence("c", c.begin(), c.end());
		print_sequence("soln", soln.begin(), soln.end());
		return 1;
	}
	else
		return 0;
}


int test_avx2_float_div() {
	std::vector<float> a(8, 5.5);
	std::vector<float> b(8, 2.2);
	std::vector<float> c(8);
	std::vector<float> soln(8, 2.5);

	auto va = avxhole::simd::avx2_load(a.data());
	auto vb = avxhole::simd::avx2_load(b.data());

	auto vc = avxhole::simd::avx2_div(va, vb);

	avxhole::simd::avx2_store(c.data(), vc);

	bool r = compare_sequences(c.begin(), c.end(), soln.begin());

	if (r == true) {
		std::cout << "\nERROR! test_avx2_float_div()" << std::endl;
		print_sequence("c", c.begin(), c.end());
		print_sequence("soln", soln.begin(), soln.end());
		return 1;
	}
	else
		return 0;
}


int test_avx2_float_fma() {
	std::vector<float> a(8, 5.5);
	std::vector<float> b(8, 2.2);
	std::vector<float> c(8, 1.1);
	std::vector<float> d(8);
	std::vector<float> soln(8, 13.2);

	auto va = avxhole::simd::avx2_load(a.data());
	auto vb = avxhole::simd::avx2_load(b.data());
	auto vc = avxhole::simd::avx2_load(c.data());

	auto vd = avxhole::simd::avx2_fma(va, vb, vc);

	avxhole::simd::avx2_store(d.data(), vd);

	bool r = compare_sequences(d.begin(), d.end(), soln.begin());

	if (r == true) {
		std::cout << "\nERROR! test_avx2_float_fma()" << std::endl;
		print_sequence("d", d.begin(), d.end());
		print_sequence("soln", soln.begin(), soln.end());
		return 1;
	}
	else
		return 0;
}


int test_avx2_float_reduce() {
	std::vector<float> a{ 1.1, 4.9, 2.3, 3.5, 5.7, 2.8, 0.6, 8.0 };
	float soln{ 28.9 };

	auto va = avxhole::simd::avx2_load(a.data());

	float s = avxhole::simd::avx2_reduce(va);

	bool r = std::abs(s - 28.9f) > 0.00001;

	if (r == true) {
		std::cout << "\nERROR! test_avx2_float_reduce()"
				  << "\ns    = " << s
				  << "\nsoln = " << soln << std::endl;
		return 1;
	}
	else
		return 0;
}