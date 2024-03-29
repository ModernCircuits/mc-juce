// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc::strings {

[[nodiscard]] auto split(juce::String const& str, char delimiter) -> std::vector<juce::String>;

template <typename T>
[[nodiscard]] auto toValue(juce::String const& str) -> T;

} // namespace mc::strings

#include "strings.cpp" // NOLINT(bugprone-suspicious-include)
