#pragma once

#include "TypeUtils.hpp"
#include <string>
#include <fstream>
#include <iostream>

struct fill
{
    template<typename TabOfData>
    void operator()(TabOfData&& output, const RawSignal& signal) const;
};

struct findLocalMinMax
{
    enum class MinOrMax : int
    {
        FindMin = -1,
        FindMax = 1
    };
    template<typename TabOfData>
    RawSignal operator()(const TabOfData&& __t, std::size_t derivativeOrder , MinOrMax minOrMax, double threshold) const;
};

template <char const *str>
struct dumpInfile
{
    template<typename TabOfData>
    void operator()(TabOfData&& __t) const
    {
        std::ofstream file;
        file.open(GetString());
        for(int i{0} ; i < __t.size() ; ++i)
        {
            file << i << ";" << __t[i].real() << std::endl;
        }
        file.close();
    }
    const char *GetString() const
    {
        return str;
    }
};

template <std::size_t windowSize, std::size_t stepSize>
struct smoothData
{
    template<typename TabOfData>
    RawSignal operator()(TabOfData&& data) const
    {
        int dataSize = data.size();
        RawSignal smoothedData;

        if (dataSize < windowSize || windowSize <= 0 || stepSize <= 0) 
        {
            std::cerr << "Invalid window size, step size, or data size!" << std::endl;
            return smoothedData;
        }

        int halfWindow = windowSize / 2;
        for (int i = halfWindow; i < dataSize; i += stepSize) 
        {
            double sum = 0.0;
            int count = 0;
            for (int j = i - halfWindow; j <= i + halfWindow; j++) 
            {
                if (j >= 0 && j < dataSize)
                {
                    sum += data[j].real();
                    count++;
                }
            }
            smoothedData.push_back(sum / count);
        }
        return smoothedData;
    }

};
