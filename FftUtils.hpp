#pragma once

#include "TypeUtils.hpp"

struct fft
{
    template<typename TabOfData>
    void operator()(TabOfData&& __t) const;
};

struct ifft
{
    template<typename TabOfData>
    void operator()(TabOfData&& __t) const;
};

struct toDb
{
    template<typename TabOfData>
    void operator()(TabOfData&& __t) const;
};