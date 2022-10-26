#include "PluginEditor.h"
#include "PluginProcessor.h"

using namespace juce;

SimpleMetronomeAudioProcessorEditor::SimpleMetronomeAudioProcessorEditor (SimpleMetronomeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
    startTimerHz (30);
}

SimpleMetronomeAudioProcessorEditor::~SimpleMetronomeAudioProcessorEditor()
{
}

void SimpleMetronomeAudioProcessorEditor::timerCallback()
{
    repaint();
}

//==============================================================================
void SimpleMetronomeAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    auto& tempoState = audioProcessor.getTempoState();
    const auto quarter = tempoState.getLastWholeQuarter();
    g.setColour (tempoState.isPlaying() ? Colours::lightgreen : Colours::white);
    g.setFont (15.0f);
    g.drawFittedText (String (quarter) + " @ " + String (tempoState.getTempo(), 2) + "BPM" + String (tempoState.getTimeSignature().numerator) + "/" + String (tempoState.getTimeSignature().denominator), getLocalBounds(), Justification::centred, 1);
}

void SimpleMetronomeAudioProcessorEditor::resized()
{
}
