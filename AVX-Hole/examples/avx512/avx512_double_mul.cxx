// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <iostream>
#include <vector>
#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>


int main()
{
  std::cout << "\nSIMD AVX512 Double Multiplication Example." << std::endl;

  // Input data
  std::vector<double> a{ 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5 };
  std::vector<double> b{ 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2 };

  // Container to store solution
  std::vector<double> c(8);

  // Define SIMD objects using input data
  auto va = avxhole::simd::avx512_load( a.data() );
  auto vb = avxhole::simd::avx512_load( b.data() );

  // Compute SIMD operation c = a * b
  auto vc = avxhole::simd::avx512_mul(va, vb);

  // Transfer data from SIMD object to container
  avxhole::simd::avx512_store(c.data(), vc);

  // Display result
  avxhole::util::print_vector("\nc", c.size(), c.data(), 3, 4);

  // c = [
  //  12.1 12.1 12.1 12.1 12.1 12.1 12.1 12.1
  // ]
}