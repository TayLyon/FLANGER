/*
  ==============================================================================

    FractionalDelay.cpp
    Created: 16 May 2019 11:29:28pm
    Author:  Taylor

  ==============================================================================
*/
//This is just an external delay line to create the small delays needed

#include "FractionalDelay.h"
#include <vector>


FractionalDelay::FractionalDelay()//---------------------------------------------------------
{
    index = 0;
    bufferSize = 0;
    buffer = NULL;
}



FractionalDelay::~FractionalDelay()//--------------------------------------------------------
{
    if (buffer) {
        delete [] buffer;
    }
}



void FractionalDelay::clear()//--------------------------------------------------------------
{
    memset(buffer, 0, bufferSize*sizeof(float));
}



void FractionalDelay::setBufferSize(int size)//----------------------------------------------
{
    if (buffer) {
        delete [] buffer;
    }
    
    bufferSize = size;
    buffer = new float[bufferSize];
    clear();
}



void FractionalDelay::addSample(float sample)//-----------------------------------------------
{
    index = getValidIndex(index);
    buffer[index] = sample;
    index++;
}



int FractionalDelay::getValidIndex(int index)//-----------------------------------------------
{
    return index % (bufferSize);
}



float FractionalDelay::linearInterpolate(float *buffer, int bufferSize, int bufferPosition)//-
{
    int lower = (int) bufferPosition;
    int upper = lower + 1;
    if (upper == bufferSize)
        upper = 0;
    float difference = bufferPosition - lower;
    
    return (buffer[upper] * difference) + (buffer[lower] * (float (1) - difference));
}



float FractionalDelay::getSample(float sampleIndex)//-----------------------------------------
{
    float localIndex = (float)index - sampleIndex;
    
    if (localIndex >= bufferSize) {
        localIndex -= bufferSize;
    }
    
    if (localIndex < 0) {
        localIndex += bufferSize;
    }

    return linearInterpolate(buffer, bufferSize, localIndex);
}
