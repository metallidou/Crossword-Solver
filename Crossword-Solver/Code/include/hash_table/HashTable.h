#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "HashTableSTRUCT.h"
#include "../vector/Vector.h"

HashTable CreateHashTable(Grid DataGrid);
void AddToHashTable(HashTable HashTable, char* Word);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------