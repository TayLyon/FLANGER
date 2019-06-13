/*
  ==============================================================================

    FractionalDelay.h
    Created: 16 May 2019 11:29:42pm
    Author:  Taylor

  ==============================================================================
*/

#pragma once

#ifndef FRACTIONALDELAY_H_INCLUDED
#define FRACTIONALDELAY_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>


class FractionalDelay
{
public:
    
    FractionalDelay();
    ~FractionalDelay();
    
    void clear();
    void setBufferSize(int size);
    void addSample(float sample);
    float getSample(float sampleIndex);
    int getValidIndex(int index);
    float linearInterpolate(float* buffer, int bufferSize, int bufferPosition);
    float operator[](float index) {return getSample(index);}
    
private:
    
    int index;
    int bufferSize;
    float* buffer;
    
};

#endif
