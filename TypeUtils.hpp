#pragma once

#include <complex>
#include <valarray>
#include <vector>

constexpr double PI = 3.141592653589793238460;

using Complex = std::complex<double>;
using CArray = std::valarray<Complex>;
using RawSignal = std::vector<double>;