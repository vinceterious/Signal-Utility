#include<iostream>
#include "AudioFile.h"
#include "PasseBand.hpp"
#include "FftUtils.hpp"
#include "Signal.hpp"

int main()
{
    AudioFile<double> audioFile;
    audioFile.load("XC629629-Common-Wood-Pigeon-Columba-palumbus.wav");
    audioFile.printSummary();
    constexpr std::size_t channel0 = 0;

    // Construct Signal
    signal::Signal inputSignal{audioFile.samples[channel0]};
    static const char rawSignal_string[] = "SignalRaw.txt";
    signal::apply<dumpInfile<rawSignal_string>>(inputSignal);

    //FFT signal and log in file
    signal::apply<fft>(inputSignal);
    static const char fftSignal_string[] = "SignalFft.txt";
    signal::apply<dumpInfile<fftSignal_string>>(inputSignal);

    //Smothed signal and log in file
    auto smothedData = signal::apply<smoothData<2048,1>>(inputSignal);
    signal::Signal smoothed{smothedData};
    static const char smoothed_string[] = "SignalSmoothed.txt";
    signal::apply<dumpInfile<smoothed_string>>(smoothed);

    //iFFT signal and log in file
    signal::apply<ifft>(inputSignal);
    static const char ifft_string[] = "SignalAfteriFft.txt";
    signal::apply<dumpInfile<ifft_string>>(inputSignal);

    /* Next step:
    CArray signalFilter;
    auto bpf = BandPassFilter(300,500,audioFile.getSampleRate(),1024);
    bpf(inputSignal.getData(),signalFilter);
    signal::Signal inputSignalFilter{signalFilter};
    signal::apply<fft>(inputSignalFilter);
    auto localMinMax = signal::apply<findLocalMinMax>(smoothed, 1, findLocalMinMax::MinOrMax::FindMin, 0.1 );
    std::ofstream myFileMinimum;
    myFileMinimum.open("exampleMinimumMax.txt");
    for(auto val : localMinMax)
        myFileMinimum 
            << val*static_cast<double>(audioFile.getSampleRate())/(static_cast<double>(audioFile.getNumSamplesPerChannel())) 
            <<";" 
            << smoothed.getData()[val].real()
            << std::endl;
    myFileMinimum.close();*/
    return 0;
}
