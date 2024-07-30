#pragma once
#include <pch.h>

struct FBuildJob 
{
    std::int32_t ID;
    float Progress;
    bool bPaused;
};