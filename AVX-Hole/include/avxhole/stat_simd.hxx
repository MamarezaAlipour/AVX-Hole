
#pragma once

#include "simd.hxx"
#include "stat/stat_impl_avx2.hxx"
#include "stat/stat_impl_avx512.hxx"
#include "stat/stat_impl_serial.hxx"
#include <vector>
#include <span>

namespace avxhole::stat {
    
    // Statistical functions with automatic SIMD dispatch
    template<typename T>
    T arithmetic_mean(std::span<const T> data) {
        if constexpr (std::same_as<T, float>) {
            if (cpu::has_avx512f() && data.size() >= 16) {
                return impl::avx512::arithmetic_mean_float(data);
            } else if (cpu::has_avx2() && data.size() >= 8) {
                return impl::avx2::arithmetic_mean_float(data);
            }
        } else if constexpr (std::same_as<T, double>) {
            if (cpu::has_avx512f() && data.size() >= 8) {
                return impl::avx512::arithmetic_mean_double(data);
            } else if (cpu::has_avx2() && data.size() >= 4) {
                return impl::avx2::arithmetic_mean_double(data);
            }
        }
        return impl::serial::arithmetic_mean(data);
    }
    
    template<typename T>
    T variance(std::span<const T> data) {
        if constexpr (std::same_as<T, float>) {
            if (cpu::has_avx512f() && data.size() >= 16) {
                return impl::avx512::variance_float(data);
            } else if (cpu::has_avx2() && data.size() >= 8) {
                return impl::avx2::variance_float(data);
            }
        } else if constexpr (std::same_as<T, double>) {
            if (cpu::has_avx512f() && data.size() >= 8) {
                return impl::avx512::variance_double(data);
            } else if (cpu::has_avx2() && data.size() >= 4) {
                return impl::avx2::variance_double(data);
            }
        }
        return impl::serial::variance(data);
    }
    
    template<typename T>
    T standard_deviation(std::span<const T> data) {
        return std::sqrt(variance(data));
    }
    
    template<typename T>
    T covariance(std::span<const T> x, std::span<const T> y) {
        if (x.size() != y.size()) {
            throw std::invalid_argument("Input arrays must have the same size");
        }
        
        if constexpr (std::same_as<T, float>) {
            if (cpu::has_avx512f() && x.size() >= 16) {
                return impl::avx512::covariance_float(x, y);
            } else if (cpu::has_avx2() && x.size() >= 8) {
                return impl::avx2::covariance_float(x, y);
            }
        } else if constexpr (std::same_as<T, double>) {
            if (cpu::has_avx512f() && x.size() >= 8) {
                return impl::avx512::covariance_double(x, y);
            } else if (cpu::has_avx2() && x.size() >= 4) {
                return impl::avx2::covariance_double(x, y);
            }
        }
        return impl::serial::covariance(x, y);
    }
    
    template<typename T>
    T correlation(std::span<const T> x, std::span<const T> y) {
        T cov = covariance(x, y);
        T std_x = standard_deviation(x);
        T std_y = standard_deviation(y);
        return cov / (std_x * std_y);
    }
    
} // namespace avxhole::stat
