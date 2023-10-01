#pragma once

#include <stdbool.h>

typedef struct FlagSTRUCT Flag; 

struct FlagSTRUCT
{
    bool horizontal_gap;        // declares if gap is horizontal
    int index;                  // gap index
};