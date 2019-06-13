/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "FractionalDelay.h"

//==============================================================================
TlflangerAudioProcessor::TlflangerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    mDelayTimeSmoothed = 0;
    mDelayTime = 0;
    mLFODepth = 0;
    mLFORate = 0;
    mFeedback = 0;
    mMix = 0;
    

addParameter   (mLFODepthParameter = new AudioParameterFloat("LFOdepth",
                                                             "LFO Depth",
                                                              0.0,
                                                              100.0,
                                                              50.0));
    
addParameter    (mLFORateParameter = new AudioParameterFloat("LFOrate",
                                                             "LFO Rate",
                                                              0.0,
                                                              15.0,
                                                              2.5));
    
addParameter        (mMixParameter = new AudioParameterFloat("mix",
                                                             "Mix",
                                                              0.0,
                                                              70.0,
                                                              35.0));
    
addParameter  (mDelayTimeParameter = new AudioParameterFloat("delaytime",
                                                             "Delay Time",
                                                              0.0,
                                                              150.0,
                                                              75.0));
    
addParameter   (mFeedbackParameter = new AudioParameterFloat("feedback",
                                                             "Feedback",
                                                              0.0,
                                                              70.0,
                                                              35.0));
}

TlflangerAudioProcessor::~TlflangerAudioProcessor()
{
}

//==============================================================================
const String TlflangerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}


bool TlflangerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TlflangerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TlflangerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TlflangerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TlflangerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TlflangerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TlflangerAudioProcessor::setCurrentProgram (int index)
{
}

const String TlflangerAudioProcessor::getProgramName (int index)
{
    return {};
}

void TlflangerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TlflangerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    SR = getSampleRate();
    
    delayL.setBufferSize(SR);
    delayR.setBufferSize(SR);
    
    toneL.setSampleRate(sampleRate);
    toneR.setSampleRate(sampleRate);
    
}

void TlflangerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TlflangerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TlflangerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
const float sampleRate = getSampleRate();
    
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
                                                                                                    // In case we have more outputs than inputs, this code clears any output
                                                                                                    // channels that didn't contain input data, (because these aren't
                                                                                                    // guaranteed to be empty - they may contain garbage).
                                                                                                    // This is here to avoid people getting screaming feedback
                                                                                                    // when they first compile a plugin, but obviously you don't need to keep
                                                                                                    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
                                                                                                    // This is the place where you'd normally do the guts of your plugin's
                                                                                                    // audio processing...
                                                                                                    // Make sure to reset the state if your inner loop is processing
                                                                                                    // the samples and the outer loop is handling the channels.
                                                                                                    // Alternatively, you can process the samples with the channels
                                                                                                    // interleaved by keeping the same state.
                                                                                                    //    float * leftChannel = buffer.getWritePointer(0);
                                                                                                    //    float * rightChannel =  buffer.getWritePointer(1);
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
                                                                                                    //lfoL.initaliseWave(rate, 1, SR, ToneGenerator::SINE);
                                                                                                    //foR.initaliseWave(rate, 1, SR, ToneGenerator::SINE);
                                                                                                    //float* channelData = buffer.getWritePointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            
            if (mLFORate == 0)
            {
                toneL.reset();                                                                      // Tone refers to the LFO wave itself
                toneR.reset();
            }
            
            toneL.setFrequency(mLFORate * 1.0);
            toneR.setFrequency(mLFORate * 1.1);
            
            float leftMod  = (toneL.tick() + 1) * mLFODepth * (sampleRate/100);
            float rightMod = (toneR.tick() + 1) * mLFODepth * (sampleRate/100);
            
            float leftSamplesDelay  =  ((mDelayTime * 15) + 0.75) * (sampleRate/1000) +  leftMod;
            float rightSamplesDelay =  ((mDelayTime * 20) + 0.5)  * (sampleRate/1000) + rightMod;
            
            float l_combined;
            float r_combined;
            
            float l_xn = buffer.getReadPointer(0)[i];
            float r_xn = buffer.getReadPointer(1)[i];
            
            float l_yn = delayL[leftSamplesDelay];
            float r_yn = delayR[rightSamplesDelay];
            
            l_combined = l_xn + l_yn * mFeedback;
            r_combined = r_xn + r_yn * mFeedback;
            
            delayL.addSample(l_combined);
            delayR.addSample(r_combined);
            
            buffer.getWritePointer(0)[i] = (l_xn * (1-mMix) + l_yn * mMix);
            buffer.getWritePointer(1)[i] = (r_xn * (1-mMix) + r_yn * mMix);
        }
    }
}

//==============================================================================
bool TlflangerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TlflangerAudioProcessor::createEditor()
{
    return new TlflangerAudioProcessorEditor (*this);
}

//==============================================================================
void TlflangerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TlflangerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TlflangerAudioProcessor();
}
