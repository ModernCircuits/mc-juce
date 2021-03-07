/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_core
 vendor:        mc
 version:       0.1.0
 name:          Core
 description:   Core JUCE extensions and utilities.
 dependencies:  juce_gui_extra, juce_events, juce_dsp

 END_JUCE_MODULE_DECLARATION
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP

#ifndef USE_MC_CORE
#define USE_MC_CORE 1
#endif

#include <juce_dsp/juce_dsp.h>
#include <juce_events/juce_events.h>
#include <juce_gui_extra/juce_gui_extra.h>

#include "fmt/chrono.h"
#include "fmt/format.h"

#include "container/flat_map.hpp"

#include "image/image_utils.hpp"
#include "javascript/json_utils.hpp"
#include "text/format.hpp"
#include "thread/thread_safe_queue.hpp"

#include "thread/background_process.hpp"

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
