#pragma once

#include "struct/HashTableSTRUCT.h"
#include "../vector/Vector.h"

HashTable CreateHashTable(DataGrid DataGrid);
void AddToHashTable(HashTable* HashTable, char* Word);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------