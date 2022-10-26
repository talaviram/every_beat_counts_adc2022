#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>

class SimpleMetronomeAudioProcessorEditor : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    SimpleMetronomeAudioProcessorEditor (SimpleMetronomeAudioProcessor&);
    ~SimpleMetronomeAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

private:
    SimpleMetronomeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMetronomeAudioProcessorEditor)
};
