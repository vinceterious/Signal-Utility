#include "FftUtils.hpp"

namespace{

void fft_impl(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    CArray even = x[std::slice(0, N/2, 2)];
    CArray odd = x[std::slice(1, N/2, 2)];

    fft_impl(even);
    fft_impl(odd);

    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

void ifft_impl(CArray& x)
{
    x = x.apply(std::conj);
    fft_impl(x);
    x = x.apply(std::conj);
    x /= x.size();
}

void toDb_impl(CArray& x)
{
    for(auto& singleComplex : x)
    {
        singleComplex = 10.0 * 0.5*std::log(singleComplex.real()*singleComplex.real()* + singleComplex.imag()*singleComplex.imag());
    }
}

}

template<>
void fft::operator()(CArray&& __t) const
{
    fft_impl(__t);
};

template<>
void ifft::operator()(CArray&& __t) const
{
    ifft_impl(__t);
};

template<>
void toDb::operator()(CArray&& __t) const
{
    toDb_impl(__t);
};