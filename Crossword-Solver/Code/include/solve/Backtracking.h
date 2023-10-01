#pragma once

#include "../grid/struct/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"
#include "struct/FlagSTRUCT.h"
#include "Gap.h"

// basic backtracking function
void Backtracking(DataGrid* DataGrid, Coordinates Gap, Flag* Flags, int *FLAG);

// this function detects a possible problematic word previously placed
Coordinates GetFaultyGap(DataGrid DataGrid, Flag* Flags, int CurrentFlag);

// remove constraints functions
void RemoveConstraints(DataGrid* DataGrid, Coordinates Gap);
void RemoveConstraintsHorizontally(DataGrid* DataGrid, Coordinates Gap);
void RemoveConstraintsVertically(DataGrid* DataGrid, Coordinates Gap);

// remove word
void RemoveWord(DataGrid* DataGrid, Coordinates* Gap, int* FLAG);