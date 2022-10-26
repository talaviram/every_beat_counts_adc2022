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
    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText (String (quarter), getLocalBounds(), Justification::centred, 1);
}

void SimpleMetronomeAudioProcessorEditor::resized()
{
}
