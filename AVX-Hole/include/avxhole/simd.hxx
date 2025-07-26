
#pragma once

#include "internal/concepts.hxx"
#include "internal/traits.hxx"
#include "internal/avx2.hxx"
#include "internal/avx512.hxx"

#include <immintrin.h>
#include <type_traits>
#include <concepts>

namespace avxhole {
    
    // Main SIMD vector wrapper
    template<typename T, std::size_t Width>
    class simd_vector {
    public:
        using value_type = T;
        static constexpr std::size_t width = Width;
        
        // Constructors
        simd_vector() = default;
        explicit simd_vector(T scalar);
        explicit simd_vector(const T* data);
        
        // Basic operations
        simd_vector operator+(const simd_vector& other) const;
        simd_vector operator-(const simd_vector& other) const;
        simd_vector operator*(const simd_vector& other) const;
        simd_vector operator/(const simd_vector& other) const;
        
        // FMA operations
        simd_vector fma(const simd_vector& b, const simd_vector& c) const;
        
        // Load/Store operations
        void load(const T* data);
        void store(T* data) const;
        
        // Reduction operations
        T reduce_add() const;
        T reduce_mul() const;
        
        // Broadcast operations
        static simd_vector broadcast(T value);
        static simd_vector zero();
        
    private:
        typename internal::simd_traits<T, Width>::register_type data_;
    };
    
    // Type aliases for common SIMD types
    using avx2_float = simd_vector<float, 8>;
    using avx2_double = simd_vector<double, 4>;
    using avx512_float = simd_vector<float, 16>;
    using avx512_double = simd_vector<double, 8>;
    
} // namespace avxhole
