#pragma once

#include "struct/DataGridSTRUCT.h"
#include "struct/VisualGridSTRUCT.h"
#include "../../include/vector/Vector.h"

// get needed grid information about word placement
DataGrid ProcessDataGrid(VisualGrid VisualGrid);

// number of words that fit in each dimension 
DataGrid NumberWordsFitHorizontally(DataGrid DataGrid, VisualGrid VisualGrid);
DataGrid NumberWordsFitVertically(DataGrid DataGrid, VisualGrid VisualGrid);

// gap lengths in each dimension
DataGrid GapsLengthsHorizontally(DataGrid DataGrid, VisualGrid VisualGrid);
DataGrid GapLengthsVertically(DataGrid DataGrid, VisualGrid VisualGrid);

// free memory
void FreeDataGrid(DataGrid* DataGrid);