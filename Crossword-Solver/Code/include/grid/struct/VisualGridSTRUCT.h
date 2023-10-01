#pragma once

#include <stdbool.h>

typedef struct VisualGridSTRUCT VisualGrid; 

struct VisualGridSTRUCT
{
    int x;                             // width of grid
    int y;                             // height of grid
    bool** black_box;                  // black boxes (we consider black boxes the gaps that can fit no letters)
};