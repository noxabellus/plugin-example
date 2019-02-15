#pragma once

#include "cstd.h"

#ifdef _WIN32
  #ifdef MODULE
    #define API __declspec(dllimport)
    #define DLL __declspec(dllexport)
  #else
    #define API __declspec(dllexport)
    #define DLL __declspec(dllimport)
  #endif
#else
  #define API
  #define DLL
#endif