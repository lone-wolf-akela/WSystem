#pragma once
#include <pch.h>

struct BuildJob 
{
    std::int32_t ID;
    float Progress;
    bool bPaused;
};