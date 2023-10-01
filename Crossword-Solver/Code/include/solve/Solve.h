#pragma once

#include "../grid/struct/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"
#include "struct/FlagSTRUCT.h"
#include "Backtracking.h"
#include "Words.h"
#include "Gap.h"

// basic function for solving crossword
void Solve(DataGrid* DataGrid, HashTable Dictionary);

// initializations
void Initialize(DataGrid* DataGrid, HashTable Dictionary);
Flag* FlagInitialize(DataGrid* DataGrid);

// to fill next gap 
void FillNext(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int* FLAG);
void FillGap(DataGrid* DataGrid, Coordinates* Gap, HashTable Dictionary, Flag* Flags, int* FLAG);

// attempt to fill crossword
void FillCrossword(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags);
