#ifndef MODERN_CIRCUITS_JUCE_MODULES_GEOMETRY_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_GEOMETRY_UTILS_HPP

template<typename ValueType>
struct juce::VariantConverter<juce::Point<ValueType>>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Point<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const x      = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const y      = mc::StringUtils::toValue<ValueType>(splits[1]);
        return juce::Point<ValueType> {x, y};
    }

    [[nodiscard]] static auto toVar(juce::Point<ValueType> const& p) -> juce::var
    {
        return juce::String {fmt::format("{}:{}", p.x, p.y)};
    }
};

template<typename ValueType>
struct juce::VariantConverter<juce::Line<ValueType>>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Line<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const startX = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const startY = mc::StringUtils::toValue<ValueType>(splits[1]);
        auto const endX   = mc::StringUtils::toValue<ValueType>(splits[2]);
        auto const endY   = mc::StringUtils::toValue<ValueType>(splits[3]);
        return juce::Line<ValueType> {{startX, startY}, {endX, endY}};
    }

    [[nodiscard]] static auto toVar(juce::Line<ValueType> const& l) -> juce::var
    {
        return juce::String {fmt::format("{}:{}:{}:{}", l.getStart().x, l.getStart().y, l.getEnd().x, l.getEnd().y)};
    }
};

template<typename ValueType>
struct juce::VariantConverter<juce::Rectangle<ValueType>>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Rectangle<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const x      = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const y      = mc::StringUtils::toValue<ValueType>(splits[1]);
        auto const width  = mc::StringUtils::toValue<ValueType>(splits[2]);
        auto const height = mc::StringUtils::toValue<ValueType>(splits[3]);
        return juce::Rectangle<ValueType> {x, y, width, height};
    }

    [[nodiscard]] static auto toVar(juce::Rectangle<ValueType> const& l) -> juce::var
    {
        return juce::String {fmt::format("{}:{}:{}:{}", l.getX(), l.getY(), l.getWidth(), l.getHeight())};
    }
};

#endif  // MODERN_CIRCUITS_JUCE_MODULES_GEOMETRY_UTILS_HPP