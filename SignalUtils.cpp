#include "SignalUtils.hpp"

namespace
{
    void fill_impl(const RawSignal& signal, CArray& output)
    {
        const auto numSamples {signal.size()};
        output.resize(numSamples);
        for (int i = 0; i < numSamples; i++)
        {
            double currentSampleReal = signal[i];
            output[i] = Complex(currentSampleReal,0);
        }
    }

    RawSignal findLocalMinMax_impl(const CArray& data, std::size_t derivativeOrder , findLocalMinMax::MinOrMax minOrMax, double threshold)
    {
        int dataSize = data.size();
        RawSignal localMinima;
        if (dataSize < derivativeOrder*2 + 1 && derivativeOrder > 0) 
        {
            std::cerr << "Data size too small to find local minima!" << std::endl;
            return localMinima;
        }
        for (std::size_t i {derivativeOrder}; i < dataSize - derivativeOrder; i+=derivativeOrder) 
        {
            double diffLeft{0};
            double diffRight{0};
            for( std::size_t k{0} ;  k < derivativeOrder ; ++k )
            {
                diffLeft+= (data[i].real() - data[i - k].real());
                diffRight+= (data[i].real() - data[i + k].real());
            }
            diffLeft = static_cast<double>(minOrMax)*diffLeft/static_cast<double>(derivativeOrder);
            diffRight = static_cast<double>(minOrMax)*diffRight/static_cast<double>(derivativeOrder);
            if (diffLeft < 0 && diffRight < 0 && std::abs(diffLeft - diffRight) > threshold)
            {
                localMinima.push_back(i);
            }
        }
        return localMinima;
    }

}

template<>
void fill::operator()(CArray&& output, const RawSignal& signal) const
{
    fill_impl(signal, output);
} 

template<>
RawSignal findLocalMinMax::operator()(const CArray&& input, std::size_t derivativeOrder , findLocalMinMax::MinOrMax minOrMax, double threshold) const
{
    return findLocalMinMax_impl(input, derivativeOrder, minOrMax, threshold);
}