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
        #define WHEEL_BREAKPOINT() __builtin_trap();
    #endif
#endif

#ifdef WHEEL_ENABLE_ASSERTS
    #define WHEEL_ASSERT(expr, ...) { if (!(expr)) { WHEEL_ERROR("Assertion failed {0}", __VA_ARGS__); WHEEL_BREAKPOINT();} else {} }
    #define WHEEL_CORE_ASSERT(expr, ...) { if (!(expr)) { WHEEL_CORE_ERROR("Core Assertion failed {0}", __VA_ARGS__); WHEEL_BREAKPOINT();} else {} }
#endif

namespace Wheel {

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using WeakRef = std::weak_ptr<T>;

}