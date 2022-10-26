#pragma once

#include <JuceHeader.h>

class TempoUtils
{
public:
    void calculatePosition (const juce::AudioPlayHead::PositionInfo pos);

    int getLastWholeQuarter() const;
    bool isPlaying() const;

    double getQuarterRateInSamples (double sampleRate) const;

    double getTempo() const;
    juce::AudioPlayHead::TimeSignature getTimeSignature() const;

    double getQuarterInSeconds() const;

private:
    bool isPlay { false };
    double ppq;
    double lastBarPpq;
    double bpm;
    juce::AudioPlayHead::TimeSignature timeSig;
};
