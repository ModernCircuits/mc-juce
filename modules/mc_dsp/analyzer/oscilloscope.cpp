namespace mc
{

Oscilloscope::Oscilloscope(OscilloscopeSource& source) : oscilloscopeSource_(source)
{
    sampleData_.fill(double(0));
    setFramesPerSecond(30);
}

auto Oscilloscope::setFramesPerSecond(int framesPerSecond) -> void
{
    jassert(framesPerSecond > 0 && framesPerSecond < 1000);
    startTimerHz(framesPerSecond);
}

auto Oscilloscope::paint(juce::Graphics& g) -> void
{
    auto const area = getLocalBounds();
    if (auto* const lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel()); lnf != nullptr)
    {
        lnf->drawOscilloscopeBackground(g, area);
        lnf->drawOscilloscopePlot(g, area, sampleData_.data(), sampleData_.size(), 1.5f, area.getHeight() / 2.0f);
    }
}

auto Oscilloscope::timerCallback() -> void
{
    sampleData_.fill(double(0));
    oscilloscopeSource_.getQueue().pop(sampleData_.data());
    repaint();
}

}  // namespace mc