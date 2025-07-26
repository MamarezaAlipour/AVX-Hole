
#pragma once

#include "concepts.hxx"
#include <immintrin.h>
#include <type_traits>

namespace avxhole::internal {
    
    // Primary template for SIMD traits
    template<typename T, std::size_t Width>
    struct simd_traits;
    
    // Specialization for AVX2 float
    template<>
    struct simd_traits<float, 8> {
        using register_type = __m256;
        using value_type = float;
        static constexpr std::size_t width = 8;
        static constexpr std::size_t alignment = 32;
        static constexpr bool is_avx2 = true;
        static constexpr bool is_avx512 = false;
    };
    
    // Specialization for AVX2 double
    template<>
    struct simd_traits<double, 4> {
        using register_type = __m256d;
        using value_type = double;
        static constexpr std::size_t width = 4;
        static constexpr std::size_t alignment = 32;
        static constexpr bool is_avx2 = true;
        static constexpr bool is_avx512 = false;
    };
    
    // Specialization for AVX-512 float
    template<>
    struct simd_traits<float, 16> {
        using register_type = __m512;
        using value_type = float;
        static constexpr std::size_t width = 16;
        static constexpr std::size_t alignment = 64;
        static constexpr bool is_avx2 = false;
        static constexpr bool is_avx512 = true;
    };
    
    // Specialization for AVX-512 double
    template<>
    struct simd_traits<double, 8> {
        using register_type = __m512d;
        using value_type = double;
        static constexpr std::size_t width = 8;
        static constexpr std::size_t alignment = 64;
        static constexpr bool is_avx2 = false;
        static constexpr bool is_avx512 = true;
    };
    
    // Helper type aliases
    template<typename T, std::size_t Width>
    using register_type_t = typename simd_traits<T, Width>::register_type;
    
    template<typename T, std::size_t Width>
    constexpr std::size_t alignment_v = simd_traits<T, Width>::alignment;
    
    template<typename T, std::size_t Width>
    constexpr bool is_avx2_v = simd_traits<T, Width>::is_avx2;
    
    template<typename T, std::size_t Width>
    constexpr bool is_avx512_v = simd_traits<T, Width>::is_avx512;
    
} // namespace avxhole::internal
