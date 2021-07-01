#ifndef MODERN_CIRCUITS_JUCE_MODULES_PLATFORM_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_PLATFORM_HPP

#if defined(_WIN32) || defined(_WIN64)
#ifndef MC_WINDOWS
#define MC_WINDOWS 1
#endif
#elif defined(__ANDROID__)
#ifndef MC_ANDROID
#define MC_ANDROID 1
#endif
#elif defined(__FreeBSD__) || (__OpenBSD__)
#ifndef MC_BSD
#define MC_BSD 1
#endif
#elif defined(__linux__) && !defined(__ANDROID__)
#ifndef MC_LINUX
#define MC_LINUX 1
#endif
#elif defined(__APPLE_CPP__) || defined(__APPLE_CC__)
#include <CoreFoundation/CoreFoundation.h>  // (needed to find out what platform we're using)

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#define MC_IPHONE 1
#define MC_IOS 1
#else
#define MC_MAC 1
#endif
#else
#error "Unknown platform!"
#endif

#if MC_WINDOWS
#ifdef _MSC_VER
#ifdef _WIN64
#define MC_64BIT 1
#else
#define MC_32BIT 1
#endif
#endif

#ifdef _DEBUG
#define MC_DEBUG 1
#endif

#ifdef __MINGW32__
#define MC_MINGW 1
#ifdef __MINGW64__
#define MC_64BIT 1
#else
#define MC_32BIT 1
#endif
#endif

#endif

/**
 * @brief Compiler type macros.
 */
#if defined(__clang__)
#define MC_COMPILER_CLANG 1
#elif defined(__GNUC__)
#define MC_COMPILER_GCC 1
#elif defined(_MSC_VER)
#define MC_COMPILER_MSVC 1
#elif defined(__INTEL_COMPILER)
#define MC_COMPILER_INTEL 1
#elif defined(__EMSCRIPTEN__)
#define MC_COMPILER_EMSCRIPTEN 1
#else
#error "unknown compiler"
#endif

/**
 * @brief Resolve which function signature macro will be used.
 */
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600))         \
    || defined(__ghs__)
#define MC_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define MC_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#define MC_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define MC_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define MC_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define MC_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define MC_FUNC_SIG __func__
#else
#define MC_FUNC_SIG "MC_FUNC_SIG unknown!"
#endif

#if defined(__has_builtin)
#define MC_HAS_BUILTIN(...) __has_builtin(__VA_ARGS__)
#else
#define MC_HAS_BUILTIN(...) 0
#endif

#if defined(__has_feature)
#define MC_HAS_FEATURE(...) __has_feature(__VA_ARGS__)
#else
#define MC_HAS_FEATURE(...) 0
#endif

/**
 * MC_ANONYMOUS_VARIABLE(str) introduces an identifier starting with
 * str and ending with a number that varies with the line.
 */
#ifndef MC_ANONYMOUS_VARIABLE
#define MC_CONCATENATE_IMPL(s1, s2) s1##s2
#define MC_CONCATENATE(s1, s2) MC_CONCATENATE_IMPL(s1, s2)

/**
 * Modular builds build each module with its own preprocessor state, meaning
 * `__COUNTER__` no longer provides a unique number across a TU.  Instead of
 * calling back to just `__LINE__`, use a mix of `__COUNTER__` and `__LINE__`
 * to try provide as much uniqueness as possible.
 */
#ifdef __COUNTER__
#if MC_HAS_FEATURE(modules)
#define MC_ANONYMOUS_VARIABLE(str) MC_CONCATENATE(MC_CONCATENATE(MC_CONCATENATE(str, __COUNTER__), _), __LINE__)
#else
#define MC_ANONYMOUS_VARIABLE(str) MC_CONCATENATE(str, __COUNTER__)
#endif
#else
#define MC_ANONYMOUS_VARIABLE(str) MC_CONCATENATE(str, __LINE__)
#endif
#endif

/**
 * Cache line sizes for ARM values are not strictly correct since cache
 * line sizes depend on implementations, not architectures.  There are even
 * implementations with cache line sizes configurable at boot time.
 */
#if defined(__aarch64__)
#define MC_CACHE_LINE_SIZE 64
#elif defined(__ARM_ARCH_5T__)
#define MC_CACHE_LINE_SIZE 32
#elif defined(__ARM_ARCH_7A__)
#define MC_CACHE_LINE_SIZE 64
#elif defined(__PPC64__)
#define MC_CACHE_LINE_SIZE 128
#elif defined(__i386__) || defined(__x86_64__)
#define MC_CACHE_LINE_SIZE 64
#else
#define MC_CACHE_LINE_SIZE alignof(max_align_t)
#endif

namespace mc
{

inline constexpr std::size_t HardwareCacheLineSize = MC_CACHE_LINE_SIZE;

}

#if (defined(MC_COMPILER_GCC) || defined(MC_COMPILER_CLANG)) && !defined(MC_MAC)
#ifndef MC_ALIGNAS
#define MC_ALIGNAS(bytes) __attribute__((aligned(bytes)))
#endif
#elif defined(MC_COMPILER_MSVC)
#ifndef MC_ALIGNAS
#define MC_ALIGNAS(bytes) __declspec(align(bytes))
#endif
#else
#define MC_ALIGNAS(bytes)
#endif

#endif  // MODERN_CIRCUITS_JUCE_MODULES_PLATFORM_HPP