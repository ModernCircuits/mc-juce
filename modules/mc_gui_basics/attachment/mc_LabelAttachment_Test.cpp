#include <mc_gui_basics/mc_gui_basics.hpp>

#include <catch2/catch.hpp>

TEST_CASE("gui_basics/attachment: LabelValueTreeAttachment", "[gui_basics][attachment]")
{
    auto const id = juce::String { "test" };
    juce::UndoManager um {};
    juce::ValueTree valueTree { "test_plugin" };
    valueTree.setProperty(id, "test", &um);

    juce::Label label { "label", "label" };
    CHECK(label.getText() == juce::String { "label" });

    mc::LabelValueTreeAttachment<juce::String> attachment { valueTree, id, label, &um };
    CHECK(label.getText() == juce::String { "test" });
}