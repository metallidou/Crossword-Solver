#pragma once

#include "../grid/struct/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"
#include "struct/FlagSTRUCT.h"
#include "Gap.h"

void RemoveConstraints(DataGrid* DataGrid, Coordinates Gap);

void RemoveConstraintsHorizontally(DataGrid* DataGrid, Coordinates Gap);
void RemoveConstraintsVertically(DataGrid* DataGrid, Coordinates Gap);

Coordinates GetFaultyGap(DataGrid DataGrid, Flag* Flags, int CurrentFlag);
void RemoveWord(DataGrid* DataGrid, Coordinates* Gap, int* FLAG);
void Backtracking(DataGrid* DataGrid, Coordinates Gap, Flag* Flags, int *FLAG);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------