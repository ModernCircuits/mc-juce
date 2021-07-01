#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_SPECTRUM_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_SPECTRUM_HPP

namespace mc
{

/**
 * @brief Component for the spectrum analyser.
 */
class Spectrum
    : public juce::Component
    , public juce::Timer
{
public:
    enum ColourIds
    {
        plot   = 0x1331600,
        grid   = 0x1331601,
        labels = 0x1331602,
    };

    class LookAndFeelMethods
    {
    public:
        virtual ~LookAndFeelMethods() = default;

        virtual auto setAnalyzerDefaults() -> void = 0;

        virtual auto getAnalyserPathBounds(juce::Rectangle<int> const& area) -> juce::Rectangle<int>           = 0;
        virtual auto getAnalyserFrequencyLabelBounds(juce::Rectangle<int> const& area) -> juce::Rectangle<int> = 0;

        virtual auto drawAnalyzerGrid(juce::Graphics& g, juce::Rectangle<int> const& area) -> void   = 0;
        virtual auto drawAnalyzerLabels(juce::Graphics& g, juce::Rectangle<int> const& area) -> void = 0;
        virtual auto drawAnalyzerPath(juce::Graphics& g, juce::Rectangle<int> const& area, juce::Path const& path)
            -> void
            = 0;
    };

    explicit Spectrum(SpectrumSource& analyser);
    ~Spectrum() override = default;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    auto timerCallback() -> void override;

    SpectrumSource& processor_;
    juce::Rectangle<int> plotFrame_;
    juce::Rectangle<int> textFrame_;
    juce::Path path_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Spectrum)  // NOLINT
};

}  // namespace mc
#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_SPECTRUM_HPP