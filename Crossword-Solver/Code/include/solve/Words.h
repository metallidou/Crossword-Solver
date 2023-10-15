#pragma once

#include "../grid/struct/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"
#include "struct/FlagSTRUCT.h"
#include "Gap.h"

// another way to symbolize a vector of words
typedef Vector Words;       

// get a dictionary with words of a constraint
Words* AttachHashTable(Coordinates Gap, HashTable HashTable);

// get a word that can fit in the gap
String FindSuitableWord(Coordinates* Gap, HashTable HashTable);

// number of appropriate words
int GetNumberOfSuitableWords(Coordinates Gap, HashTable HashTable);

// place word on gap
void PlaceWord(DataGrid* DataGrid, Coordinates* Gap, String Word, int *FLAG);

// check whether a word will create problematic constraints for another gap, so as to minimize backtracks
bool IsWordAcceptable(DataGrid DataGrid, Coordinates Gap, HashTable HashTable);