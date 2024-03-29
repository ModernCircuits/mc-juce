// SPDX-License-Identifier: BSL-1.0
#include <mc_core/mc_core.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/javascript: JSONUtils::loadFromURL", "[core]")
{
    auto url  = juce::URL { "https://jsonplaceholder.typicode.com/users" };
    auto json = mc::JSONUtils::loadFromURL(url);
    REQUIRE(json.getArray()->size() == 10);
}
