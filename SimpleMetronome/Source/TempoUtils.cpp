#include "TempoUtils.h"

using namespace juce;

void TempoUtils::calculatePosition (const AudioPlayHead::PositionInfo pos)
{
    if (pos.getPpqPosition().hasValue())
        ppq = *pos.getPpqPosition();
    else
        ppq = 0.0;

    if (pos.getPpqPositionOfLastBarStart().hasValue())
        lastBarPpq = *pos.getPpqPositionOfLastBarStart();
    else
        lastBarPpq = 0.0;

    isPlay = pos.getIsPlaying();

    if (pos.getBpm().hasValue())
        bpm = *pos.getBpm();
    else
        bpm = 120.0;

    if (pos.getTimeSignature().hasValue())
        timeSig = *pos.getTimeSignature();
    else
        timeSig = { 4, 4 };
}

int TempoUtils::getLastWholeQuarter() const
{
    return static_cast<int> (floor (ppq));
}

double TempoUtils::getSubQuarterDivision() const
{
    return ppq - getLastWholeQuarter();
}

bool TempoUtils::isPlaying() const
{
    return isPlay;
}

double TempoUtils::getTempo() const
{
    return bpm;
}

juce::AudioPlayHead::TimeSignature TempoUtils::getTimeSignature() const
{
    return timeSig;
}

double TempoUtils::getQuarterInSeconds() const
{
    // beat per second
    return bpm / 60.0;
}

double TempoUtils::getDenominatorRatioToQuarters() const
{
    return 4.0 / static_cast<double> (getTimeSignature().denominator);
}
