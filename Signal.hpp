#pragma once

#include "SignalUtils.hpp"

namespace signal
{
class Signal
{
public:
    Signal(const RawSignal& );
    Signal(const CArray& );
    const CArray& getData() const { return data; };
    const std::size_t size() const { return data.size(); };
    void resize(std::size_t n){ data.resize(n);};

private:
    CArray data{};
    template <class T,  class... Args>
    friend auto apply(Signal& input, Args... args) -> decltype(T{}(std::forward<CArray>(input.data), args...));
 }; 

template <class Op, class... Args>
auto apply(Signal& input, Args... args)
    -> decltype(Op{}(std::forward<CArray>(input.data), args...))
{
    return Op{}(std::forward<CArray>(input.data), args...);
}

}