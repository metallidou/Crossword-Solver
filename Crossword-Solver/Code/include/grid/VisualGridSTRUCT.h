#ifndef VISUAL_GRID_STRUCT_H
#define VISUAL_GRID_STRUCT_H

#include <stdbool.h>

typedef struct VisualGridSTRUCT VisualGrid; 

//-------------------------------------- VISUAL GRID ----------------------------------------------------------------------------------

struct VisualGridSTRUCT
{
    int x;                              // width of grid
    int y;                              // height of grid
    bool** black_box;                  // stores black boxes (we consider black boxes the gaps that can fit no letters)
};

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------