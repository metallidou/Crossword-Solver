#ifndef SOLVE_H
#define SOLVE_H

#include "../grid/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"
#include "FlagSTRUCT.h"

void Solve(DataGrid* DataGrid, HashTable Dictionary);
void Initialize(DataGrid* DataGrid, Flag* Flags, HashTable Dictionary);

void IntersectionsHorizontally(DataGrid* DataGrid);
void IntersectionsVertically(DataGrid* DataGrid);

void SetGapsFillingOrder(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag);

void SolveCrossword(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags);
void GetGapToFill(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag);
void ChooseWordToFillGap(DataGrid* DataGrid, Coordinates* Gap, HashTable Dictionary, Flag* Flags, int CurrentFlag);

Vector SetWordsVector(Coordinates Gap, HashTable Dictionary);
String GetWord(Coordinates* Gap, HashTable Dictionary);
int GetWordsNumber(Coordinates Gap, HashTable Dictionary);

void PlaceWord(DataGrid* DataGrid, Coordinates* Gap, String Word);
bool IsValid(DataGrid DataGrid, Coordinates Gap, HashTable Dictionary);

// CONSTRAINTS
void AddConstraints(DataGrid* DataGrid, Coordinates Gap);
void RemoveConstraints(DataGrid* DataGrid, Coordinates Gap);

void AddConstraintsHorizontally(DataGrid* DataGrid, Coordinates Gap);
void AddConstraintsVertically(DataGrid* DataGrid, Coordinates Gap);

void RemoveConstraintsHorizontally(DataGrid* DataGrid, Coordinates Gap);
void RemoveConstraintsVertically(DataGrid* DataGrid, Coordinates Gap);

// BACKTRACKING
Coordinates GetFaultyGap(DataGrid DataGrid, Flag* Flags, int CurrentFlag);
void RemoveWord(DataGrid* DataGrid, Coordinates* Gap);
void Backtracking(DataGrid* DataGrid, Coordinates Gap, Flag* Flags, int CurrentFlag);
int IsHorizontalGap(Coordinates Gap);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------