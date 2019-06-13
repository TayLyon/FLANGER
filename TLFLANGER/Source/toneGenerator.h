/*
  ==============================================================================

    toneGenerator.h
    Created: 16 May 2019 11:30:15pm
    Author:  Taylor

  ==============================================================================
*/

#pragma once

#ifndef TONEGENERATOR_H_INCLUDED
#define TONEGENERATOR_H_INCLUDED
#include <math.h>

class ToneGenerator
{
public:
    
    ToneGenerator();
    
    void setFrequency(int frequency);
    void setSampleRate(int sampleRate);
    void reset();
    float tick();
    
private:
    
    double twoPI;    //removed Const Double
    double kFrequency;
    double kPhase;
    double kSampleRate;
    double kPhaseIncrement;
    void updateIncrement();
    
};

#endif
