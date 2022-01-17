#pragma once

#define WHEEL_ENABLE_ASSERTS

#ifdef WHEEL_PLATFORM_WINDOWS
    #define WHEEL_BREAKPOINT() DebugBreak()
    #ifdef WHEEL_DYNAMIC_LIBRARY
        #define WHEEL_API __declspec(dllexport)
    #else
        #define WHEEL_API __declspec(dllimport)
    #endif
#else
    #ifdef WHEEL_PLATFORM_MAC
        #define __builtin_trap();
    #endif
#endif

#ifdef WHEEL_ENABLE_ASSERTS
    #define WHEEL_ASSERT(expr, ...) { if (!(expr)) { WHEEL_ERROR("Assertion failed {0}", __VA_ARGS__); WHEEL_BREAKPOINT();} else {} }
    #define WHEEL_CORE_ASSERT(expr, ...) { if (!(expr)) { WHEEL_CORE_ERROR("Core Assertion failed {0}", __VA_ARGS__); WHEEL_BREAKPOINT();} else {} }
#endif