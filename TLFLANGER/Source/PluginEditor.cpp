/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TlflangerAudioProcessorEditor::TlflangerAudioProcessorEditor (TlflangerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    auto& params = processor.getParameters(); //Making the alias to the parameters
    
//NOW FOR THE SLIDERS
//DEPTH========================================================================
    
    AudioParameterFloat* LFODepthParameter = (AudioParameterFloat*)params.getUnchecked(0);
    
    mLFODepthSlider.setBounds(20,(getHeight() / 2) - 25, 75, 75);
    mLFODepthSlider.setRange(LFODepthParameter->range.start, LFODepthParameter->range.end);
    mLFODepthSlider.setSkewFactor(0.5);
    mLFODepthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    mLFODepthSlider.setValue(*LFODepthParameter);
    addAndMakeVisible(mLFODepthSlider);
    
    mLFODepthSlider.onValueChange = [this, LFODepthParameter]
    {processor.mLFODepth = mLFODepthSlider.getValue() / 100; };
    
    mLFODepthSlider.onDragStart = [LFODepthParameter]
    {LFODepthParameter->beginChangeGesture(); };
    
    mLFODepthSlider.onDragEnd = [LFODepthParameter]
    {LFODepthParameter->endChangeGesture(); };
    
    mLFODepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 25);
    mLFODepthSlider.setTextValueSuffix("%");
    
    depthLabel.setText("Depth", dontSendNotification);
    depthLabel.attachToComponent(&mLFODepthSlider, false);
    depthLabel.setJustificationType(Justification::centred);
    
    addAndMakeVisible(&depthLabel);
    mLFODepthSlider.addListener(this);
    
//RATE==========================================================================
    
    AudioParameterFloat* LFORateParameter = (AudioParameterFloat*)params.getUnchecked(1);
    
    mLFORateSlider.setBounds(95, (getHeight() / 2) - 25, 75, 75);
    mLFORateSlider.setRange(LFORateParameter->range.start, LFORateParameter->range.end);
//    mLFORateSlider.setSkewFactor(0.5);
    mLFORateSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    mLFORateSlider.setValue(*LFORateParameter);
    addAndMakeVisible(mLFORateSlider);
    
    mLFORateSlider.onValueChange = [this, LFORateParameter]
    {processor.mLFORate = mLFORateSlider.getValue(); };
    
    mLFORateSlider.onDragStart = [LFORateParameter]
    {LFORateParameter->beginChangeGesture(); };
    
    mLFORateSlider.onDragEnd = [LFORateParameter]
    {LFORateParameter->endChangeGesture(); };
    
    mLFORateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 25);
    mLFORateSlider.setTextValueSuffix("ms");
    
    rateLabel.setText("Rate", dontSendNotification);
    rateLabel.attachToComponent(&mLFORateSlider, false);
    rateLabel.setJustificationType(Justification::centred);
    
    addAndMakeVisible(&rateLabel);
    mLFORateSlider.addListener(this);
   
//MIX===========================================================================
    
    AudioParameterFloat* MixParameter = (AudioParameterFloat*)params.getUnchecked(2);
    
    mMixSlider.setBounds(170, (getHeight() / 2) - 25, 75, 75);
    mMixSlider.setRange(MixParameter->range.start, MixParameter->range.end);
    mMixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    mMixSlider.setValue(*MixParameter);
    addAndMakeVisible(mMixSlider);
    
    mMixSlider.onValueChange = [this, MixParameter]
    {processor.mMix = mMixSlider.getValue() / 100; };
    
    mMixSlider.onDragStart = [MixParameter]
    {MixParameter->beginChangeGesture(); };
    
    mMixSlider.onDragEnd = [MixParameter]
    {MixParameter->endChangeGesture(); };
    
    mMixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 25);
    mMixSlider.setTextValueSuffix("%");
    
    mixLabel.setText("Mix", dontSendNotification);
    mixLabel.attachToComponent(&mMixSlider, false);
    mixLabel.setJustificationType(Justification::centred);
    
    addAndMakeVisible(&mixLabel);
    mMixSlider.addListener(this);
  
//DELAY=========================================================================
    
    AudioParameterFloat* DelayTimeParameter = (AudioParameterFloat*)params.getUnchecked(3);
    
    mDelayTimeSlider.setBounds(245, (getHeight() / 2) - 25, 75, 75);
    mDelayTimeSlider.setRange(DelayTimeParameter->range.start, DelayTimeParameter->range.end);
    mDelayTimeSlider.setSkewFactor(0.5);
    mDelayTimeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    mDelayTimeSlider.setValue(*DelayTimeParameter);
    addAndMakeVisible(mDelayTimeSlider);
    
    mDelayTimeSlider.onValueChange = [this, DelayTimeParameter]
    {processor.mDelayTime = mDelayTimeSlider.getValue() / 1000; };
    
    mDelayTimeSlider.onDragStart = [DelayTimeParameter]
    {DelayTimeParameter->beginChangeGesture(); };
    
    mDelayTimeSlider.onDragEnd = [DelayTimeParameter]
    {DelayTimeParameter->endChangeGesture(); };
    
    mDelayTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 25);
    mDelayTimeSlider.setTextValueSuffix("%");
    
    delayLabel.setText("Delay", dontSendNotification);
    delayLabel.attachToComponent(&mDelayTimeSlider, false);
    delayLabel.setJustificationType(Justification::centred);
    
    addAndMakeVisible(&delayLabel);
    mDelayTimeSlider.addListener(this);
    
//FEEDBACK=======================================================================
    
    AudioParameterFloat* FeedbackParameter = (AudioParameterFloat*)params.getUnchecked(4);
    
    mFeedbackSlider.setBounds(320, (getHeight() / 2) - 25, 75, 75);
    mFeedbackSlider.setRange(FeedbackParameter->range.start, FeedbackParameter->range.end);
    mFeedbackSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    mFeedbackSlider.setValue(*FeedbackParameter);
    addAndMakeVisible(mFeedbackSlider);
    
    mFeedbackSlider.onValueChange = [this, FeedbackParameter]
    {processor.mFeedback = mFeedbackSlider.getValue() / 100; };
    
   mFeedbackSlider.onDragStart = [FeedbackParameter]
    {FeedbackParameter->beginChangeGesture(); };
    
    mFeedbackSlider.onDragEnd = [FeedbackParameter]
    {FeedbackParameter->endChangeGesture(); };
    
    mFeedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 25);
    mFeedbackSlider.setTextValueSuffix("%");
    
    feedbackLabel.setText("Feedback", dontSendNotification);
    feedbackLabel.attachToComponent(&mFeedbackSlider, false);
    feedbackLabel.setJustificationType(Justification::centred);
    
    addAndMakeVisible(&feedbackLabel);
    mFeedbackSlider.addListener(this);
    
}

TlflangerAudioProcessorEditor::~TlflangerAudioProcessorEditor()
{
}

//==============================================================================
void TlflangerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::grey);
    g.setFont (100.0f);
    g.drawFittedText ("FLANGER", getLocalBounds(), Justification::centred, getHeight() / 4);
}

void TlflangerAudioProcessorEditor::resized()
{
}

void TlflangerAudioProcessorEditor::sliderValueChanged(Slider *Slider)
{
}
