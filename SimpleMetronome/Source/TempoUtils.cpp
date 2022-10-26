#include "TempoUtils.h"

using namespace juce;

void TempoUtils::calculatePosition (const AudioPlayHead::PositionInfo pos)
{
    if (pos.getPpqPosition().hasValue())
        ppq = *pos.getPpqPosition();
    else
        ppq = 0.0;

    isPlay = pos.getIsPlaying();
}

int TempoUtils::getLastWholeQuarter() const
{
    return static_cast<int> (floor (ppq));
}

bool TempoUtils::isPlaying() const
{
    return isPlay;
}
