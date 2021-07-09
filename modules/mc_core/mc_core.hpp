/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_core
 vendor:        mc
 version:       0.1.0
 name:          Modern Circuits JUCE Core module
 description:   Core JUCE extensions and utilities.
 dependencies:  juce_core, juce_events, juce_audio_basics, mc_external

 END_JUCE_MODULE_DECLARATION
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP

#ifndef USE_MC_CORE
#define USE_MC_CORE 1
#endif

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>

#include <mc_external/mc_external.hpp>

#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>
#include <mutex>
#include <thread>
#include <type_traits>

#include "system/mc_Platform.hpp"

#include "system/mc_Assert.hpp"
#include "system/mc_CRTP.hpp"

#include "text/mc_Format.hpp"
#include "text/mc_StringUtils.hpp"
#include "text/mc_TextValueConverters.hpp"

#include "container/mc_Registry.hpp"
#include "container/mc_Variant.hpp"
#include "container/mc_Vector.hpp"

#include "javascript/mc_JSONUtils.hpp"
#include "math/mc_Constants.hpp"
#include "math/mc_RangeUtils.hpp"
#include "time/mc_TimeUtils.hpp"

#include "thread/LockFreeQueue.hpp"
#include "thread/mc_ThreadSafeQueue.hpp"

#include "thread/mc_BackgroundProcess.hpp"
#include "thread/mc_LeftRight.hpp"

#include "benchmark/mc_Profile.hpp"

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
