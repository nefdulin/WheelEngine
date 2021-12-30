#pragma once

#ifdef WHEEL_PLATFORM_WINDOWS
    #ifdef WHEEL_DYNAMIC_LIBRARY
        #define WHEEL_API __declspec(dllexport)
    #else
        #define WHEEL_API __declspec(dllimport)
    #endif
#else
    #define WHEEL_API
    #define WHEEL_ENABLE_ASSERTS
#endif

#ifdef WHEEL_ENABLE_ASSERTS
    #define WHEEL_ASSERT(expr, ...) { if (!(expr)) { WHEEL_ERROR("Assertion failed {0}", __VA_ARGS__); __builtin_trap();();} else {} }
    #define WHEEL_CORE_ASSERT(expr, ...) { if (!(expr)) { WHEEL_CORE_ERROR("Core Assertion failed {0}", __VA_ARGS__); __builtin_trap();} else {} }
#endif