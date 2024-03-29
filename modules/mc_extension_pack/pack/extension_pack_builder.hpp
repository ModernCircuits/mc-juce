// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace mc {

struct ExtensionPackBuilder {
    ExtensionPackSpecs spec;
    FlatMap<std::string, AssetLoader> loaders;
};

[[nodiscard]] auto build(ExtensionPackBuilder const& builder) -> juce::Result;

} // namespace mc
