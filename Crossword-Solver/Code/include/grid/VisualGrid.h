#pragma once

#include "struct/VisualGridSTRUCT.h"

// read file and get needed information
VisualGrid CreateVisualGrid(char* GridFile);

// width and height of grid
int GetGridDimensions(char* GridFile);

// placement of black boxes 
void GetBlackBoxes(VisualGrid Grid, char* GridFile);

// free memory
void FreeVisualGrid(VisualGrid* VisualGrid);