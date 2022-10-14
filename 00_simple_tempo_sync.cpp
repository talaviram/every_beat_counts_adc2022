double bpmToMillis (double newBpm)
{
    const auto beatPerSecond = newBpm / 60.0;
    // returns beat per millisecond...
    return beatPerSecond / 1000.0;
}

void process (float** audioBuffer, double currentHostBpm)
{
    constexpr auto BASE_QUARTER = 4;
    auto musicalDelayParam = 8; // eight note. 1/8

    double delayInMs = bpmToMillis (currentHostBpm) / (BASE_QUARTER / musicalDelayParam);

    // multiply by sample-rate...
    // use params in audio sample context
}