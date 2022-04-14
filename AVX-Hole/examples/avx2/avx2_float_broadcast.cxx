// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <iostream>
#include <vector>
#include <avxhole/simd.hxx>
#include <avxhole/util.hxx>


int main()
{
  std::cout << "\nSIMD AVX2 Float Broadcast Example." << std::endl;

  // Container to store solution
  std::vector<float> a(8);

  // Scalar value
  float s = 5.5;

  // Broadcast scalar value to each element of SIMD object
  auto va = avxhole::simd::avx2_broadcast(&s);

  // Transfer data from SIMD object to container
  avxhole::simd::avx2_store(a.data(), va);

  // Display result
  avxhole::util::print_vector("\na", a.size(), a.data(), 2, 3);

  // a = [
  //  5.5 5.5 5.5 5.5 5.5 5.5 5.5 5.5
  // ]
}