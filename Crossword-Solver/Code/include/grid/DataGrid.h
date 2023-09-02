#ifndef DATA_GRID_H
#define DATA_GRID_H

#include "DataGridSTRUCT.h"
#include "VisualGridSTRUCT.h"

DataGrid ProcessDataGrid(VisualGrid VisualGrid);
DataGrid NumberWordsFitHorizontally(DataGrid DataGrid, VisualGrid VisualGrid);
DataGrid NumberWordsFitVertically(DataGrid DataGrid, VisualGrid VisualGrid);
DataGrid GapsLengthsHorizontally(DataGrid DataGrid, VisualGrid VisualGrid);
DataGrid GapLengthsVertically(DataGrid DataGrid, VisualGrid VisualGrid);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------