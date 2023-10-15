#pragma once

#include "../grid/struct/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"
#include "struct/FlagSTRUCT.h"
#include "Backtracking.h"
#include "Words.h"
#include "Gap.h"

// basic function for solving crossword
void Solve(DataGrid* DataGrid, HashTable HashTable);

// initializations
void Initialize(DataGrid* DataGrid, HashTable HashTable);
Flag* FlagInitialize(DataGrid* DataGrid);

// to fill next gap 
void FillNext(DataGrid* DataGrid, HashTable HashTable, Flag* Flags, int* FLAG);
void FillGap(DataGrid* DataGrid, Coordinates* Gap, HashTable HashTable, Flag* Flags, int* FLAG);

// attempt to fill crossword
void FillCrossword(DataGrid* DataGrid, HashTable HashTable, Flag* Flags);
