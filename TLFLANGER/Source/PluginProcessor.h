/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "toneGenerator.h"
#include "FractionalDelay.h"
#include "ParamSmooth.h"


//==============================================================================
/**
*/
class TlflangerAudioProcessor  : public AudioProcessor,
                                 public ChangeBroadcaster
{
public:
    
    float  mLFODepth;
    float  mLFODepthSmoothed;
    float  mLFORate;
    float  mMix;
    float  mDelayTime;
    float  mDelayTimeSmoothed;
    float  mFeedback;
    
    //==============================================================================
    TlflangerAudioProcessor();
    ~TlflangerAudioProcessor();
    
   

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    
    ToneGenerator lfoL;
    ToneGenerator lfoR;
    ToneGenerator toneL;
    ToneGenerator toneR;
    
    FractionalDelay delayL;
    FractionalDelay delayR;
    
    double SR;
    float LFO;
    int lfoSize;
    float inputData;
    float flangedData;
    
    AudioParameterFloat * mLFODepthParameter;
    AudioParameterFloat * mLFORateParameter;
    AudioParameterFloat * mMixParameter;
    AudioParameterFloat * mDelayTimeParameter;
    AudioParameterFloat * mFeedbackParameter;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TlflangerAudioProcessor)
};

#endif
