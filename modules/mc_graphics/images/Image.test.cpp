#include "mc_graphics/mc_graphics.hpp"

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("graphics/images: VariantConverter<juce::Image>", "[graphics]")
{
    SECTION("rgb cleared")
    {
        auto const original = juce::Image { juce::Image::RGB, 2, 2, true };
        auto const value    = juce::VariantConverter<juce::Image>::toVar(original);
        auto const result   = juce::VariantConverter<juce::Image>::fromVar(value);
        REQUIRE(original.isValid() == result.isValid());
        REQUIRE(original.getBounds() == result.getBounds());
        REQUIRE(original.getFormat() == result.getFormat());
    }
}
