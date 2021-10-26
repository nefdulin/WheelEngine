#pragma once


#ifdef WHEEL_PLATFORM_WINDOWS
    #ifdef WHEEL_DYNAMIC_LIBRARY
        #define WHEEL_API __declspec(dllexport)
    #else
        #define WHEEL_API __declspec(dllimport)
    #endif
#else
    #define WHEEL_API
#endif