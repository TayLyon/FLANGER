/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TlflangerAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    TlflangerAudioProcessorEditor (TlflangerAudioProcessor&);
    ~TlflangerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
 
    void sliderValueChanged (Slider* slider) override;
    
    Slider mLFODepthSlider;
    Label depthLabel;
    
    Slider mLFORateSlider;
    Label rateLabel;
    
    Slider mMixSlider;
    Label mixLabel;
    
    Slider mDelayTimeSlider;
    Label delayLabel;
    
    Slider mFeedbackSlider;
    Label feedbackLabel;
    
    AudioParameterFloat * mLFODepthParameter;
    AudioParameterFloat * mLFORateParameter;
    AudioParameterFloat * mMixParameter;
    AudioParameterFloat * mDelayTimeParameter;
    AudioParameterFloat * mFeedbackParameter;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TlflangerAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TlflangerAudioProcessorEditor)
};

#endif
