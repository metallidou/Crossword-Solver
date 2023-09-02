#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../grid/DataGridSTRUCT.h"
#include "../hash_table/HashTable.h"

HashTable ProcessDictionary(DataGrid DataGrid, char* DictionaryFile);
bool IsWithinBounds(DataGrid DataGrid, String Word);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------