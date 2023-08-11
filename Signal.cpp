#include "Signal.hpp"
#include "SignalUtils.hpp"

namespace signal
{
Signal::Signal(const RawSignal& input)
    : data{}
{
    apply<fill>(*this, input);
}

Signal::Signal(const CArray& input)
    : data{input}
{
}
}