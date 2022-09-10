#pragma once

namespace mc {

/// \brief Text & float converter for active/bypass.
struct ActiveTextConverter {
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return value > 0.5F ? juce::translate("active") : juce::translate("bypassed");
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float
    {
        return static_cast<float>(text == juce::translate("active"));
    }
};

/// \brief Text & float converter for frequency.
struct FrequencyTextConverter {
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return (value < 1000) ? juce::String(value, 0) + " Hz" : juce::String(value / 1000.0, 2) + " kHz";
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float
    {
        return text.endsWith(" kHz") ? static_cast<float>(text.dropLastCharacters(4).getFloatValue() * 1000.0)
                                     : static_cast<float>(text.dropLastCharacters(3).getFloatValue());
    }
};

/// \brief Text & float converter for filter quality.
struct QualityTextConverter {
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {

        juce::ignoreUnused(maxStringLength);
        return { value, 1 };
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float { return text.getFloatValue(); }
};

/// \brief Text & float converter for percentages.
struct PercentTextConverter {
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return juce::String(value * 100.0F, 1) + " %";
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float
    {
        return text.dropLastCharacters(2).getFloatValue() / 100.0F;
    }
};

/// \brief Text & float converter for durations based on seconds.
struct TimeSecondsTextConverter {
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return juce::String(value, 2) + " s";
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float
    {
        return text.dropLastCharacters(2).getFloatValue();
    }
};

/// \brief Text & float converter for durations based on seconds.
struct TimeMillisecondsTextConverter {
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return juce::String(value, 1) + " ms";
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float
    {
        return text.dropLastCharacters(3).getFloatValue();
    }
};

/// \brief Text & float converter for gain.
struct GainTextConverter {
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return juce::String(juce::Decibels::gainToDecibels(value), 1) + " dB";
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float
    {
        return juce::Decibels::decibelsToGain(text.dropLastCharacters(3).getFloatValue());
    }
};

/// \brief Text & float converter for phase invert.
struct InvertPhaseTextConverter {
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return value < 0.5 ? "Normal" : "Inverted";
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float { return text == "Normal" ? 0.0F : 1.0F; }
};

struct InvertPhaseBoolTextConverter {
public:
    MC_NODISCARD auto operator()(bool value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return !value ? "Normal" : "Inverted";
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> bool { return text != "Normal"; }
};

struct RatioCompTextConverter {
public:
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);

        if (value > 30.F) { return "Limiter"; }
        if (value < 10.F) { return "1:" + juce::String(value, 1); }
        return "1:" + juce::String(static_cast<int>(value));
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float { return text.substring(2).getFloatValue(); }
};

struct RatioExpTextConverter {
public:
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);

        if (value == 21.F) { return "Gate"; }
        if (value < 10.F) { return juce::String(value, 1) + ":1"; }
        return juce::String(static_cast<int>(value)) + ":1";
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float
    {
        return text.dropLastCharacters(2).getFloatValue();
    }
};

} // namespace mc
