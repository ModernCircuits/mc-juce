namespace mc {

Oscilloscope::Oscilloscope(OscilloscopeSource& source) : source_ { source } { source_.addChangeListener(this); }

Oscilloscope::~Oscilloscope() { source_.removeChangeListener(this); }

auto Oscilloscope::paint(juce::Graphics& g) -> void
{
    auto* const lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel());
    if (lnf != nullptr) {
        auto const area = getLocalBounds();
        lnf->drawOscilloscopeBackground(g, area);
        lnf->drawOscilloscopePlot(g, area, source_, 1.5f, static_cast<float>(area.getHeight()) / 2.0f);
    }
}

auto Oscilloscope::changeListenerCallback(juce::ChangeBroadcaster* /*source*/) -> void { repaint(); }

} // namespace mc