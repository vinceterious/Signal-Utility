#include "Signal.hpp"
#include "SignalUtils.hpp"

namespace signal
{
Signal::Signal(const RawSignal& input)
    : data{}
{
    SignalUtils::fill(input, data);
}

Signal::Signal(const CArray& input)
    : data{input}
{
}
}