#pragma once

#include "struct/HashTableSTRUCT.h"
#include "../vector/Vector.h"

// initialize hash table
HashTable CreateHashTable(DataGrid DataGrid);

// add words to hash table
void AddToHashTable(HashTable* HashTable, char* Word);