#pragma once

#include <JuceHeader.h>

class TempoUtils
{
public:
    void calculatePosition (const juce::AudioPlayHead::PositionInfo pos);

    int getLastWholeQuarter() const;
    bool isPlaying() const;

private:
    bool isPlay { false };
    double ppq;
};
