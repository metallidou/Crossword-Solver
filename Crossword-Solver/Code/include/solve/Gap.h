#pragma once

#include "../grid/struct/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"
#include "struct/FlagSTRUCT.h"
#include "Words.h"

bool IsGapPrioritySet(Flag* Flags, int CurrentFlag);

void SetIntersections(DataGrid* DataGrid);
void IntersectionsHorizontally(DataGrid* DataGrid);
void IntersectionsVertically(DataGrid* DataGrid);

void SetGapsFillingOrder(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag, int GapOrder);
void SetGapsFillingOrder_1(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag);
void SetGapsFillingOrder_2(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag);

Coordinates GetGap(DataGrid DataGrid, Flag* Flags, int CurrentFlag);

// CONSTRAINTS
void AddConstraints(DataGrid* DataGrid, Coordinates Gap);

void AddConstraintsHorizontally(DataGrid* DataGrid, Coordinates Gap);
void AddConstraintsVertically(DataGrid* DataGrid, Coordinates Gap);

int IsHorizontalGap(Coordinates Gap);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------