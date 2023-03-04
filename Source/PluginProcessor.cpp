/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PlainChorusAudioProcessor::PlainChorusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), treestate(*this, nullptr, "PARAMS", createParameterLayout())
                            
#endif
{
}

PlainChorusAudioProcessor::~PlainChorusAudioProcessor()
{
}

//Vector of parameters
juce::AudioProcessorValueTreeState::ParameterLayout PlainChorusAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    auto cRate =  std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"RATE", 1}, "Rate", 0, 100 ,30);
    auto cDepth = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"DEPTH", 1}, "Depth", juce::NormalisableRange<float>(0.0f, 1.0f ), 0.3f);
    auto cDelay = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"DELAY", 1}, "Delay", 0, 100, 25);
    auto cFeedback = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FEEDBACK", 1}, "Feedback", juce::NormalisableRange<float>(-1.0f, 1.0f), 0.0f);
    auto cMix = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"MIX", 1}, "Mix", juce::NormalisableRange<float>(0.0f, 1.0f), 0.3f);
    
    
    params.push_back(std::move(cRate));
    params.push_back(std::move(cDepth));
    params.push_back(std::move(cDelay));
    params.push_back(std::move(cFeedback));
    params.push_back(std::move(cMix));
    
    
    return{params.begin(), params.end()};
    
    
}






//==============================================================================
const juce::String PlainChorusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PlainChorusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PlainChorusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PlainChorusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PlainChorusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PlainChorusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PlainChorusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PlainChorusAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PlainChorusAudioProcessor::getProgramName (int index)
{
    return {};
}

void PlainChorusAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PlainChorusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PlainChorusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PlainChorusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void PlainChorusAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* inputBuffer = buffer.getReadPointer(channel);
        auto* outputBuffer = buffer.getWritePointer(channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            
        }

        
    }
}

//==============================================================================
bool PlainChorusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PlainChorusAudioProcessor::createEditor()
{
    //return new PlainChorusAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void PlainChorusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PlainChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PlainChorusAudioProcessor();
}
