
# AVX-Hole

[![MIT license](https://img.shields.io/badge/License-MIT-brightgreen.svg)](https://github.com/MamarezaAlipour/AVX-Hole/blob/master/LICENSE)
[![Standard](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen.svg)]()

A lightweight, header-only C++20 library providing a modern interface for AVX2 and AVX-512 x86 SIMD instruction sets with statistical computing capabilities.

---

## 🚀 Features

- **Header-only library** - No compilation required, just include headers
- **Modern C++20** - Uses concepts, type traits, and modern C++ features
- **AVX2 & AVX-512 Support** - Comprehensive SIMD operations for both instruction sets
- **Type Safety** - Compile-time type checking with concepts
- **Statistical Functions** - Built-in statistical operations optimized for SIMD
- **Performance Benchmarks** - Included performance comparison tools
- **Cross-platform** - Works on any x86-64 system with AVX support

## 📋 Requirements

- **Compiler**: GCC 10+ or Clang 12+ with C++20 support
- **CPU**: x86-64 processor with AVX2 support (AVX-512 optional)
- **OS**: Linux, macOS, or Windows

## 🛠️ Installation

This is a header-only library. Simply copy the `include/avxhole` directory to your project:

```bash
# Clone the repository
git clone https://github.com/MamarezaAlipour/AVX-Hole.git

# Copy headers to your project
cp -r AVX-Hole/include/avxhole /path/to/your/project/include/
```

## 🏃 Quick Start

### Basic SIMD Operations

```cpp
#include <avxhole/simd.hxx>
#include <iostream>
#include <vector>

int main() {
    // AVX2 float operations (8 elements)
    std::vector<float> a = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    std::vector<float> b = {8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    std::vector<float> result(8);
    
    // Create SIMD vectors
    avxhole::avx2_float va(a.data());
    avxhole::avx2_float vb(b.data());
    
    // Perform operations
    auto sum = va + vb;
    auto product = va * vb;
    auto fma_result = va.fma(vb, sum); // a * b + sum
    
    // Store results
    sum.store(result.data());
    
    return 0;
}
```

### Statistical Operations

```cpp
#include <avxhole/stat_simd.hxx>
#include <vector>

int main() {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    
    // Calculate mean using SIMD
    double mean = avxhole::stat::arithmetic_mean_avx2(data.data(), data.size());
    
    // Calculate variance
    double variance = avxhole::stat::variance_avx2(data.data(), data.size());
    
    // Calculate standard deviation
    double std_dev = avxhole::stat::standard_deviation_avx2(data.data(), data.size());
    
    return 0;
}
```

## 📚 API Reference

### Core SIMD Types

- `avxhole::avx2_float` - 8-element float vector (AVX2)
- `avxhole::avx2_double` - 4-element double vector (AVX2)
- `avxhole::avx512_float` - 16-element float vector (AVX-512)
- `avxhole::avx512_double` - 8-element double vector (AVX-512)

### Basic Operations

#### Arithmetic Operations
```cpp
// Addition, subtraction, multiplication, division
auto result = va + vb;
auto result = va - vb;
auto result = va * vb;
auto result = va / vb;

// Fused multiply-add
auto result = va.fma(vb, vc); // va * vb + vc
```

#### Load/Store Operations
```cpp
// Load from aligned memory
simd_vector<float, 8> v(data_ptr);

// Store to memory
v.store(output_ptr);

// Load from unaligned memory
v.load(unaligned_data_ptr);
```

#### Reduction Operations
```cpp
// Sum all elements
float sum = v.reduce_add();

// Multiply all elements
float product = v.reduce_mul();
```

#### Broadcast Operations
```cpp
// Create vector with all elements set to value
auto v = avxhole::avx2_float::broadcast(3.14f);

// Create zero vector
auto zero = avxhole::avx2_float::zero();
```

### Statistical Functions

#### Descriptive Statistics
```cpp
// Arithmetic mean
double mean = avxhole::stat::arithmetic_mean_avx2(data, size);

// Variance
double var = avxhole::stat::variance_avx2(data, size);

// Standard deviation
double std_dev = avxhole::stat::standard_deviation_avx2(data, size);
```

#### Correlation and Covariance
```cpp
// Covariance between two datasets
double cov = avxhole::stat::covariance_avx2(x_data, y_data, size);

// Correlation coefficient
double corr = avxhole::stat::correlation_avx2(x_data, y_data, size);
```

## 🏗️ Building Examples

```bash
cd AVX-Hole

# Build all examples
make examples

# Build only AVX2 examples
make avx2

# Build only AVX-512 examples
make avx512

# Build statistical examples
make stat

# Build performance benchmarks
make benchmark

# Run tests
make test
```

## 📊 Performance

The library provides significant performance improvements over scalar operations:

- **AVX2**: Up to 8x speedup for float operations, 4x for double
- **AVX-512**: Up to 16x speedup for float operations, 8x for double
- **Statistical functions**: 3-10x speedup depending on operation complexity

Run the benchmark examples to see performance comparisons on your system:

```bash
make benchmark
./build/benchmark/performance_comparison
```

## 📁 Project Structure

```
AVX-Hole/
├── include/avxhole/           # Header files
│   ├── simd.hxx              # Main SIMD interface
│   ├── stat_simd.hxx         # Statistical functions
│   ├── util.hxx              # Utility functions
│   ├── internal/             # Internal implementation
│   │   ├── concepts.hxx      # C++20 concepts
│   │   ├── traits.hxx        # Type traits
│   │   ├── avx2.hxx         # AVX2 implementations
│   │   └── avx512.hxx       # AVX-512 implementations
│   └── stat/                 # Statistical implementations
│       ├── stat_impl_avx2.hxx
│       ├── stat_impl_avx512.hxx
│       ├── stat_impl_serial.hxx
│       └── stat_prng.hxx
├── examples/                 # Example programs
│   ├── avx2/                # AVX2 examples
│   ├── avx512/              # AVX-512 examples
│   ├── stat-simd-impl/      # Statistical examples
│   └── benchmark/           # Performance benchmarks
├── tests/                   # Unit tests
└── Makefile                # Build configuration
```

## 🧪 Examples

### Matrix Multiplication
```cpp
#include <avxhole/simd.hxx>

void matrix_multiply_avx2(const float* A, const float* B, float* C, 
                         size_t rows, size_t cols, size_t inner) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; j += 8) {
            avxhole::avx2_float sum = avxhole::avx2_float::zero();
            
            for (size_t k = 0; k < inner; ++k) {
                auto a_vec = avxhole::avx2_float::broadcast(A[i * inner + k]);
                avxhole::avx2_float b_vec(&B[k * cols + j]);
                sum = sum + a_vec * b_vec;
            }
            
            sum.store(&C[i * cols + j]);
        }
    }
}
```

### Statistical Analysis
```cpp
#include <avxhole/stat_simd.hxx>

void analyze_dataset(const std::vector<double>& data) {
    auto mean = avxhole::stat::arithmetic_mean_avx2(data.data(), data.size());
    auto variance = avxhole::stat::variance_avx2(data.data(), data.size());
    auto std_dev = sqrt(variance);
    
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Std Dev: " << std_dev << std::endl;
}
```

## 🔧 Compiler Flags

When using this library, make sure to enable the appropriate SIMD instruction sets:

```bash
# For AVX2 support
g++ -std=c++20 -mavx2 -mfma -O3 -march=native your_code.cpp

# For AVX-512 support
g++ -std=c++20 -mavx512f -mavx512dq -O3 -march=native your_code.cpp
```

## ⚠️ Development Status

**This project is currently under active development and is not stable yet.**

- ✅ Basic SIMD operations (AVX2/AVX-512)
- ✅ Statistical functions
- ✅ Type safety with concepts
- ✅ Comprehensive examples
- 🚧 Advanced mathematical functions
- 🚧 Complete test coverage
- 🚧 Documentation improvements
- 📋 Performance optimizations
- 📋 Additional statistical operations

**Please use only for development and testing purposes.**

## 🤝 Contributing

Contributions are welcome! Please feel free to submit issues, feature requests, or pull requests.

### Development Guidelines
- Follow C++20 best practices
- Use concepts for type safety
- Include comprehensive tests
- Maintain header-only design
- Document new features

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Intel for the comprehensive AVX instruction set documentation
- The C++20 standardization committee for concepts and modern features
- Contributors and testers who help improve this library

## 📞 Support

- Create an issue for bug reports or feature requests
- Check the examples directory for usage patterns
- Review the test files for detailed API usage

---

**Made with ❤️ for high-performance computing**
