#pragma once

#include "../grid/struct/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"
#include "struct/FlagSTRUCT.h"
#include "Gap.h"

typedef Vector Words;

Words AttachDictionary(Coordinates Gap, HashTable Dictionary);
String FindSuitableWord(Coordinates* Gap, HashTable Dictionary);
int GetNumberOfSuitableWords(Coordinates Gap, HashTable Dictionary);

void PlaceWord(DataGrid* DataGrid, Coordinates* Gap, String Word, int *FLAG);
bool IsWordAcceptable(DataGrid DataGrid, Coordinates Gap, HashTable Dictionary);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------