
#pragma once

#include "internal/concepts.hxx"
#include <memory>
#include <cstdlib>

namespace avxhole {
    
    // Memory alignment utilities
    template<std::size_t Alignment>
    void* aligned_alloc(std::size_t size) {
        void* ptr = nullptr;
        if (posix_memalign(&ptr, Alignment, size) != 0) {
            return nullptr;
        }
        return ptr;
    }
    
    template<std::size_t Alignment>
    void aligned_free(void* ptr) {
        free(ptr);
    }
    
    // RAII wrapper for aligned memory
    template<typename T, std::size_t Alignment = 32>
    class aligned_vector {
    public:
        explicit aligned_vector(std::size_t size) 
            : size_(size), data_(static_cast<T*>(aligned_alloc<Alignment>(size * sizeof(T)))) {
            if (!data_) {
                throw std::bad_alloc();
            }
        }
        
        ~aligned_vector() {
            aligned_free(data_);
        }
        
        // Non-copyable, movable
        aligned_vector(const aligned_vector&) = delete;
        aligned_vector& operator=(const aligned_vector&) = delete;
        
        aligned_vector(aligned_vector&& other) noexcept 
            : size_(other.size_), data_(other.data_) {
            other.data_ = nullptr;
            other.size_ = 0;
        }
        
        aligned_vector& operator=(aligned_vector&& other) noexcept {
            if (this != &other) {
                aligned_free(data_);
                size_ = other.size_;
                data_ = other.data_;
                other.data_ = nullptr;
                other.size_ = 0;
            }
            return *this;
        }
        
        T* data() { return data_; }
        const T* data() const { return data_; }
        std::size_t size() const { return size_; }
        
        T& operator[](std::size_t index) { return data_[index]; }
        const T& operator[](std::size_t index) const { return data_[index]; }
        
    private:
        std::size_t size_;
        T* data_;
    };
    
    // CPU feature detection
    namespace cpu {
        bool has_avx2();
        bool has_avx512f();
        bool has_fma();
    }
    
} // namespace avxhole
