#pragma once

#include <JuceHeader.h>

class TempoUtils
{
public:
    void calculatePosition (const juce::AudioPlayHead::PositionInfo pos);

    int getLastWholeQuarter() const;

private:
    double ppq;
};
