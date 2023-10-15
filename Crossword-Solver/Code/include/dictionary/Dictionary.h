#pragma once
#include "../grid/struct/DataGridSTRUCT.h"
#include "../vector/Vector.h"
#include "../hash_table/HashTable.h"

typedef Vector Words;       

// this function reads a dictionary file and adds words to the hash table
HashTable ProcessDictionary(DataGrid DataGrid, char* DictionaryFile);

// this function declares whether a word is apropriate for placement on the crossword
bool IsWithinBounds(DataGrid DataGrid, String Word);