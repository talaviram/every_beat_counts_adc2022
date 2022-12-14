#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <optional>
using namespace juce;

SimpleMetronomeAudioProcessor::SimpleMetronomeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                          .withInput ("Input", AudioChannelSet::stereo(), true)
#endif
                          .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
}

SimpleMetronomeAudioProcessor::~SimpleMetronomeAudioProcessor()
{
}

const String SimpleMetronomeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleMetronomeAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SimpleMetronomeAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool SimpleMetronomeAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double SimpleMetronomeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleMetronomeAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
        // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleMetronomeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleMetronomeAudioProcessor::setCurrentProgram (int)
{
}

const String SimpleMetronomeAudioProcessor::getProgramName (int)
{
    return {};
}

void SimpleMetronomeAudioProcessor::changeProgramName (int, const String&)
{
}

void SimpleMetronomeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void SimpleMetronomeAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleMetronomeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void SimpleMetronomeAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (auto* playhead = getPlayHead())
    {
        const auto pos = playhead->getPosition();
        if (pos.hasValue())
            tempoUtils.calculatePosition (*pos);
    }

    if (! tempoUtils.isPlaying())
        return;

    const auto denominatorRatio = tempoUtils.getDenominatorRatioToQuarters();
    const auto beatInSamples = (getSampleRate() / tempoUtils.getQuarterInSeconds()) * denominatorRatio;
    auto nextBeatInSamples = roundToInt ((1.0 - tempoUtils.getSubDivisionForDenominator()) * beatInSamples);
    auto nextBeat = tempoUtils.getCurrentBeat() + 1;

    if (tempoUtils.getSubDivisionForDenominator() == 0.0)
        nextBeatInSamples = 0;

    while (nextBeatInSamples < buffer.getNumSamples())
    {
        // beats starts at 1; no modulo
        if (nextBeat > tempoUtils.getTimeSignature().numerator)
            nextBeat = 1;

        const auto beatGain = nextBeat == 1 ? 0.8f : 0.3f;
        std::optional<int> tickAt;

        if (nextBeatInSamples < buffer.getNumSamples())
            tickAt = nextBeatInSamples;

        if (tickAt.has_value())
        {
            for (int channel = 0; channel < totalNumOutputChannels; ++channel)
                buffer.setSample (channel, *tickAt, beatGain);

            // move to next tick
            nextBeatInSamples = roundToInt (nextBeatInSamples + beatInSamples);
            nextBeat++;
        }
    }
}

bool SimpleMetronomeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleMetronomeAudioProcessor::createEditor()
{
    return new SimpleMetronomeAudioProcessorEditor (*this);
}

void SimpleMetronomeAudioProcessor::getStateInformation (MemoryBlock&)
{
    // SampleMetronome won't save state!
}

void SimpleMetronomeAudioProcessor::setStateInformation (const void*, int)
{
    // SampleMetronome won't restore state!
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleMetronomeAudioProcessor();
}
