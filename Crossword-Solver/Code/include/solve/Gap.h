#pragma once

#include "../grid/struct/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"
#include "struct/FlagSTRUCT.h"
#include "Words.h"

// check if a gap priority is set
bool IsGapPrioritySet(Flag* Flags, int CurrentFlag);

// get a gap according to index and placement
Coordinates GetGap(DataGrid DataGrid, Flag* Flags, int CurrentFlag);

// detect intersected gaps horizontally and vertically
void SetIntersections(DataGrid* DataGrid);
void IntersectionsHorizontally(DataGrid* DataGrid);
void IntersectionsVertically(DataGrid* DataGrid);

// set gaps filling order, according to 2 approaches
void SetGapsFillingOrder(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag, int GapOrder);
// 1st approach:    
//Fill in first the gaps with the smallest number of possible words that can be placed 
void SetGapsFillingOrder_1(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag);
// 2nd approach:    
//Fill in first the gaps with the most intersections
void SetGapsFillingOrder_2(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag);

// constraint management functions
void AddConstraints(DataGrid* DataGrid, Coordinates Gap);
void AddConstraintsHorizontally(DataGrid* DataGrid, Coordinates Gap);
void AddConstraintsVertically(DataGrid* DataGrid, Coordinates Gap);

// checks if gap is horizontal or not
int IsHorizontalGap(Coordinates Gap);