#pragma once

template <>
struct juce::VariantConverter<juce::File> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> juce::File { return juce::File { v.toString() }; }
    MC_NODISCARD static auto toVar(juce::File const& file) -> juce::var { return file.getFullPathName(); }
};

template <>
struct fmt::formatter<juce::File> : formatter<string_view> {
    template <typename FormatContext>
    auto format(juce::File const& file, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", file.getFullPathName());
    }
};
