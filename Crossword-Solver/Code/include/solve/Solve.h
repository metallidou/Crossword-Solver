#ifndef SOLVE_H
#define SOLVE_H

#include "../grid/GridData.h"
#include "../hash_table/HashTable.h"
#include "../queue/Queue.h"
#include "Sort.h"

Grid Solve(Grid DataGrid, HashTable Dictionary);
void Initialize(Grid DataGrid, HashTable Dictionary);

Grid IntersectionsHorizontally(Grid DataGrid);
Grid IntersectionsVertically(Grid DataGrid);

Grid SetFlags(Grid DataGrid, Flags* FlagsLink);
Grid SetGapsFillingOrder(Grid DataGrid, Flags* FlagLink);
Grid FillGaps(Grid DataGrid, HashTable Dictionary, Flags* FlagsLink);
Grid GetGapToFill(Grid DataGrid, HashTable Dictionary, int flag, Flags* FlagsLink);
Grid ChooseWordToFillGap(Grid DataGrid, struct Grid_WORD_COORDINATES Gap, HashTable Dictionary, char* Word);
bool GapHasConstraints(struct Grid_WORD_COORDINATES Gap);

struct Grid_WORD_COORDINATES PutWordsOnVector(struct Grid_WORD_COORDINATES Gap, HashTable Dictionary);
Grid PlaceWord(Grid DataGrid, struct Grid_WORD_COORDINATES Gap, char* Word);

// CONSTRAINTS
Grid AddConstraints(Grid DataGrid, struct Grid_WORD_COORDINATES Gap);
Grid RemoveConstraints(Grid DataGrid, struct Grid_WORD_COORDINATES Gap);

Grid AddConstraintsHorizontally(Grid DataGrid, struct Grid_WORD_COORDINATES Gap);
Grid AddConstraintsVertically(Grid DataGrid, struct Grid_WORD_COORDINATES Gap);

Grid RemoveConstraintsHorizontally(Grid DataGrid, struct Grid_WORD_COORDINATES Gap);
Grid RemoveConstraintsVertically(Grid DataGrid, struct Grid_WORD_COORDINATES Gap);

// BACKTRACKING
struct Grid_WORD_COORDINATES GetFaultyGap(Grid DataGrid, struct Grid_WORD_COORDINATES Gap);
Grid RemoveWord(Grid DataGrid, struct Grid_WORD_COORDINATES Gap);
Grid RemoveAffectedWords(Grid DataGrid, struct Grid_WORD_COORDINATES Gap);
Grid Backtracking(Grid DataGrid, struct Grid_WORD_COORDINATES Gap, HashTable Dictionary);
int IsHorizontalGap(struct Grid_WORD_COORDINATES Gap);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------