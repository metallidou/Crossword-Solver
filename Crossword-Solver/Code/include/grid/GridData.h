#include "GridSTRUCT.h"
#define MAX(x,y) (((x) > (y)) ? (x) : (y)) 

// ------------------------------------ DEFINE GRID DATA --------------------------------------------------------------------------------------------------------

#ifndef GRID_DATA_H
#define GRID_DATA_H

//---- main function to process grid information (word lengths that fit horizontally or vertically, etc.) ----//
Grid ProcessGridData(GridVisual VisualGrid);

// this function inticates how many words can fit in the grid horizontally
Grid NumberWordsFitHorizontally(Grid DataGrid, GridVisual VisualGrid);

// this function inticates how many words can fit in the grid vertically
Grid NumberWordsFitVertically(Grid DataGrid, GridVisual VisualGrid);

// this function writes down the coordinates of a word horizontally (ex. length = 4, start_index = 1 and end_index = 5 (on grid), horizontally)
Grid GapsLengthsHorizontally(Grid DataGrid, GridVisual VisualGrid);

// this function writes down the coordinates of a word vertically
Grid GapLengthsVertically(Grid DataGrid, GridVisual VisualGrid);

// this function links vertical gaps with the intersected horizontal gaps 
Grid IntersectionsHorizontally(Grid DataGrid);

// this function links horizontal gaps with the intersected vertical gaps
Grid IntersectionsVertically(Grid DataGrid);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------