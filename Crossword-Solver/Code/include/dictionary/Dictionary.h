#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../grid/GridSTRUCT.h"
#include "../hash_table/HashTable.h"

HashTable ProcessDictionary(Grid DataGrid, char* DictionaryFile);
void UpdateDataGrid(Grid DataGrid, HashTable HashTable);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------