/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_gui_extra
    vendor:             Modern Circuits
    version:            0.1.0
    name:               GUI Extras
    description:        JUCE gui extra extensions and utilities.
    dependencies:       juce_gui_extra, mc_gui_basics
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_GUI_EXTRA
    #define USE_MC_GUI_EXTRA
#endif

#include <juce_gui_extra/juce_gui_extra.h>
#include <mc_gui_basics/mc_gui_basics.hpp>

// clang-format off
#include "property/value_property_component.hpp"
#include "property/color_property_component.hpp"
#include "property/file_property_component.hpp"
// clang-format on
