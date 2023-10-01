#pragma once

#include "struct/DataGridSTRUCT.h"
#include "struct/VisualGridSTRUCT.h"

DataGrid ProcessDataGrid(VisualGrid VisualGrid);
DataGrid NumberWordsFitHorizontally(DataGrid DataGrid, VisualGrid VisualGrid);
DataGrid NumberWordsFitVertically(DataGrid DataGrid, VisualGrid VisualGrid);
DataGrid GapsLengthsHorizontally(DataGrid DataGrid, VisualGrid VisualGrid);
DataGrid GapLengthsVertically(DataGrid DataGrid, VisualGrid VisualGrid);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------