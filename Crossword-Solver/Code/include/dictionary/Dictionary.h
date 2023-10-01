#pragma once
#include "../grid/struct/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"

HashTable ProcessDictionary(DataGrid DataGrid, char* DictionaryFile);
bool IsWithinBounds(DataGrid DataGrid, String Word);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------