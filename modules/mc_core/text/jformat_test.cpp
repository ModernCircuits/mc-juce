// SPDX-License-Identifier: BSL-1.0
#include <mc_core/mc_core.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/text: format", "[core]")
{
    REQUIRE(fmt::format("{0}test{0}{1}", 143, juce::String { "foo" }) == "143test143foo");
}

TEST_CASE("core/text: jformat", "[core]")
{
    REQUIRE(mc::jformat("test") == "test");
    REQUIRE(mc::jformat("test{}", 143) == "test143");
    REQUIRE(mc::jformat("{}test", 143) == "143test");
    REQUIRE(mc::jformat("{0}test{0}", 143) == "143test143");
    REQUIRE(mc::jformat("{0}test{0}{1}", 143, juce::String { "foo" }) == "143test143foo");
}
