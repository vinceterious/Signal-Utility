#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include "TypeUtils.hpp"

class BandPassFilter {
private:
    std::vector<double> coefficients;

public:
    BandPassFilter(double f1, double f2, double fs, int order) {
        coefficients.resize(order + 1, 0.0);

        double omega1 = 2.0 * PI * f1 / fs;
        double omega2 = 2.0 * PI * f2 / fs;
        for (int i = 0; i <= order; i++) {
            if (i == order / 2) {
                coefficients[i] = (omega2 - omega1) / PI;
            } else {
                double n = i - order / 2;
                coefficients[i] = (std::sin(omega2 * n) - std::sin(omega1 * n)) / (PI * n);
            }
        }
    }

    void operator()(const CArray& input, CArray& output) 
    {
        int order = coefficients.size() - 1;
        output.resize(input.size());
        for (size_t i = order; i < input.size(); i++) 
        {
            output[i] = 0;
            for (int j = 0; j <= order; j++) 
            {
                output[i] += coefficients[j] * input[i - j];
            }
        }
    }
};