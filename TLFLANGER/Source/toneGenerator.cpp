/*
  ==============================================================================

    toneGenerator.cpp
    Created: 16 May 2019 11:29:57pm
    Author:  Taylor

  ==============================================================================
*/
//Tone Generator is what creates the wave for the LFO

#include "toneGenerator.h"


ToneGenerator::ToneGenerator() : twoPI(2*(2*acos(0.0)))//-------------------------------------
{
    kSampleRate = 44100;
    kFrequency = 0.0;
    kPhase = 0.0;
    updateIncrement();
}



void ToneGenerator::setFrequency(int frequency)//-------------------------------------------
{
    kFrequency = frequency;
    updateIncrement();
}



void ToneGenerator::setSampleRate(int sampleRate)//-----------------------------------------
{
    kSampleRate = sampleRate;
    updateIncrement();
}



void ToneGenerator::updateIncrement()//--------------------------------------------------------
{
    kPhaseIncrement = kFrequency * twoPI / kSampleRate;
}



void ToneGenerator::reset()//------------------------------------------------------------------
{
    kPhase = 0.0;
}



float ToneGenerator::tick()//------------------------------------------------------------------
{
    float wave = sin(kPhase);
    kPhase += kPhaseIncrement;
    while (kPhase >= twoPI)
    {
        kPhase -= twoPI;
    }
    return wave;
}
