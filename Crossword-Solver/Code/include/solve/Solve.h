#pragma once

#include "../grid/struct/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"
#include "struct/FlagSTRUCT.h"
#include "Backtracking.h"
#include "Words.h"
#include "Gap.h"

void Solve(DataGrid* DataGrid, HashTable Dictionary);
void FillNext(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int* FLAG);
void FillGap(DataGrid* DataGrid, Coordinates* Gap, HashTable Dictionary, Flag* Flags, int* FLAG);

void Initialize(DataGrid* DataGrid, HashTable Dictionary);
Flag* FlagInitialize(DataGrid* DataGrid);

void IntersectionsHorizontally(DataGrid* DataGrid);
void IntersectionsVertically(DataGrid* DataGrid);

void FillCrossword(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------