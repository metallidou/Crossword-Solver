#ifndef SOLVE_H
#define SOLVE_H

#include "../grid/GridData.h"
#include "../hash_table/HashTable.h"
#include "Sort.h"

Grid Solve(Grid DataGrid, HashTable Dictionary);
Flags* FlagsInitialize(Grid DataGrid, Flags* Flags);
void Initialize(Grid DataGrid, HashTable Dictionary);

Grid IntersectionsHorizontally(Grid DataGrid);
Grid IntersectionsVertically(Grid DataGrid);

Grid SetFlags(Grid DataGrid, Flags* Flags);
Grid SetGapsFillingOrder(Grid DataGrid, Flags* Flag);

Grid SolveCrossword(Grid DataGrid, HashTable Dictionary, Flags* Flags);
Grid GetGapToFill(Grid DataGrid, HashTable Dictionary, Flags* Flags, int CurrentFlag);
Grid ChooseWordToFillGap(Grid DataGrid, struct GridCOORDINATES Gap, HashTable Dictionary, Flags* Flags, int CurrentFlag);

Vector SetWordsVector(struct GridCOORDINATES Gap, HashTable Dictionary);
String GetWord(struct GridCOORDINATES Gap, HashTable Dictionary);

Grid PlaceWord(Grid DataGrid, struct GridCOORDINATES Gap, char* Word);
bool IsValid(Grid DataGrid, struct GridCOORDINATES Gap, HashTable Dictionary);

// CONSTRAINTS
Grid AddConstraints(Grid DataGrid, struct GridCOORDINATES Gap);
Grid RemoveConstraints(Grid DataGrid, struct GridCOORDINATES Gap);

Grid AddConstraintsHorizontally(Grid DataGrid, struct GridCOORDINATES Gap);
Grid AddConstraintsVertically(Grid DataGrid, struct GridCOORDINATES Gap);

Grid RemoveConstraintsHorizontally(Grid DataGrid, struct GridCOORDINATES Gap);
Grid RemoveConstraintsVertically(Grid DataGrid, struct GridCOORDINATES Gap);

// BACKTRACKING
struct GridCOORDINATES GetFaultyGap(Grid DataGrid, struct GridCOORDINATES Gap, Flags* Flags, int CurrentFlag);
Grid RemoveWord(Grid DataGrid, struct GridCOORDINATES Gap);
Grid RemoveAffectedWords(Grid DataGrid, struct GridCOORDINATES Gap);
Grid Backtracking(Grid DataGrid, struct GridCOORDINATES Gap, Flags* Flags, int CurrentFlag);
int IsHorizontalGap(struct GridCOORDINATES Gap);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------