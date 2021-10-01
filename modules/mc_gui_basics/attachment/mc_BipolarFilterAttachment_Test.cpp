#include <mc_gui_basics/mc_gui_basics.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("gui_basics/attachment: BipolarFilterValueTreeAttachment", "[gui_basics][attachment]")
{
    juce::Identifier const id { "value" };
    juce::UndoManager undoManager {};
    juce::ValueTree valueTree { "test" };

    mc::CachedAtomicFloat value { valueTree, id, &undoManager };
    value = 0.5f;

    mc::BipolarFilter slider { "filter" };
    mc::BipolarFilterValueTreeAttachment attachment { valueTree, id, slider, &undoManager };
    CHECK(slider.getValue() == Catch::Approx(0.5f));

    slider.setValue(0.25f);
    CHECK(value.get() == Catch::Approx(0.25f));
    CHECK(slider.getValue() == Catch::Approx(0.25f));

    value = -0.5f;
    CHECK(value.get() == Catch::Approx(-0.5f));
    CHECK(slider.getValue() == Catch::Approx(-0.5f));
}