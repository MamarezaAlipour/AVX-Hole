// Copyright (c) 2022 Parisa Khaleghi
// All rights reserved

#include <iostream>
#include <vector>
#include <nola/simd.hxx>
#include <nola/util.hxx>


int main()
{
  std::cout << "\nSIMD AVX2 Float Fused Multiply-Add Example." << std::endl;

  // Input data
  std::vector<float> a{ 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5 };
  std::vector<float> b{ 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2, 2.2 };
  std::vector<float> c{ 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1 };

  // Container to store solution
  std::vector<float> d(8);

  // Define SIMD objects using input data
  auto va = nola::simd::avx2_load( a.data() );
  auto vb = nola::simd::avx2_load( b.data() );
  auto vc = nola::simd::avx2_load( c.data() );

  // Compute SIMD operation d = (a * b) + c
  auto vd = nola::simd::avx2_fma(va, vb, vc);

  // Transfer data from SIMD object to container
  nola::simd::avx2_store( d.data(), vd );

  // Display result
  nola::util::print_vector("\nd", d.size(), d.data(), 3, 4);

  // d = [
  //  13.2 13.2 13.2 13.2 13.2 13.2 13.2 13.2
  // ]
}