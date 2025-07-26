
#pragma once

#include <concepts>
#include <type_traits>

namespace avxhole::internal {
    
    // Concept for floating point types supported by AVX
    template<typename T>
    concept simd_floating_point = std::floating_point<T> && 
        (std::same_as<T, float> || std::same_as<T, double>);
    
    // Concept for valid SIMD widths
    template<std::size_t Width>
    concept valid_simd_width = (Width == 4) || (Width == 8) || (Width == 16);
    
    // Concept for AVX2 compatible types
    template<typename T, std::size_t Width>
    concept avx2_compatible = simd_floating_point<T> && 
        ((std::same_as<T, float> && Width == 8) || 
         (std::same_as<T, double> && Width == 4));
    
    // Concept for AVX-512 compatible types
    template<typename T, std::size_t Width>
    concept avx512_compatible = simd_floating_point<T> && 
        ((std::same_as<T, float> && Width == 16) || 
         (std::same_as<T, double> && Width == 8));
    
    // Concept for arithmetic operations
    template<typename T>
    concept arithmetic_type = std::is_arithmetic_v<T>;
    
    // Concept for aligned memory
    template<typename T>
    concept aligned_pointer = std::is_pointer_v<T> && 
        requires(T ptr) {
            { reinterpret_cast<std::uintptr_t>(ptr) % 32 == 0 };
        };
        
} // namespace avxhole::internal
