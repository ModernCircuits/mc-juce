/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_gui_basics
 vendor:        mc
 version:       0.1.0
 name:          Graphics
 description:   JUCE graphics extensions and utilities.
 dependencies:  juce_gui_basics, mc_data_structures

 END_JUCE_MODULE_DECLARATION
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_GUI_BASICS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_GUI_BASICS_HPP

#ifndef USE_MC_GUI_BASICS
    #define USE_MC_GUI_BASICS 1
#endif

#include <juce_gui_basics/juce_gui_basics.h>
#include <mc_data_structures/mc_data_structures.hpp>

#include "button/ButtonUtils.hpp"

#include "mouse/MouseUtils.hpp"

#include "widget/Components.hpp"
#include "widget/XYPad.hpp"

#include "attachment/LabelAttachment.hpp"
#include "attachment/SliderAttachment.hpp"

#endif // MODERN_CIRCUITS_JUCE_MODULES_MC_GUI_BASICS_HPP
