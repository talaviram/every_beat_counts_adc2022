#pragma once

#include <JuceHeader.h>

class TempoUtils
{
public:
    void calculatePosition (const juce::AudioPlayHead::PositionInfo pos);
    // returns current beat. starting at 1 [1-numerator]
    int getCurrentBeat() const;
    int getLastWholeQuarter() const;
    double getSubQuarterDivision() const;
    int getLastWholeAsDenominator() const;
    double getSubDivisionForDenominator() const;
    bool isPlaying() const;

    double getQuarterRateInSamples (double sampleRate) const;

    double getTempo() const;
    juce::AudioPlayHead::TimeSignature getTimeSignature() const;

    double getQuarterInSeconds() const;
    double getDenominatorRatioToQuarters() const;

private:
    bool isPlay { false };
    double ppq;
    double lastBarPpq;
    double bpm;
    juce::AudioPlayHead::TimeSignature timeSig;
};
