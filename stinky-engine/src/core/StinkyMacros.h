//
// Created by christian on 5/3/20.
//
#pragma once

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
/* Windows x64/x86 */
#ifdef _WIN64
    /* Windows x64  */
#define SK_PLATFORM_WINDOWS
#else
    /* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define SK_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define SK_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
#define SK_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define PLATFORM_LINUX
#else
/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection

#ifdef DEBUG
#if defined(PLATFORM_WINDOWS)
#define ENABLE_ASSERTS
#define DEBUGBREAK() __debugbreak()
#elif defined(PLATFORM_LINUX)

#include <signal.h>
#include <memory>

#define DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define ENABLE_ASSERTS
#else
#define DEBUGBREAK()
#endif

namespace stinky {
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args &&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args &&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#define STINKY_BIND(function) std::bind(&function, this, std::placeholders::_1)

#ifdef ENABLE_ASSERTS
#define STINKY_LOG_ERROR_AND_BREAK(...) { STINKY_ERROR(__VA_ARGS__); DEBUGBREAK();}
#else
#define STINKY_LOG_ERROR_AND_BREAK(...)
#endif

#define AssertLogIf(x, ...) { if((x)) { STINKY_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
#define AssertLogUnless(x, ...) { if(!(x)) { STINKY_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }

#define ReturnIf(x, ...) { if(x) { return __VA_ARGS__;}}
#define ReturnUnless(x, ...) { if(!(x)) { return __VA_ARGS__;}}

#define AssertReturnIf(x, ...) { if(x) { STINKY_LOG_ERROR_AND_BREAK("Assertion Failed: {0} {1} {2}", __FILE__, __LINE__ , __FUNCTION__); return __VA_ARGS__;}}
#define AssertReturnUnless(x, ...) { if(!x) { STINKY_LOG_ERROR_AND_BREAK("Assertion Failed: {0} {1} {2}", __FILE__, __LINE__ , __FUNCTION__); return __VA_ARGS__;}}

#define ContinueIf(x) { if(x) { continue;}}
#define ContinueUnless(x) { if(!(x)) { continue;}}
