#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/dictionary/Dictionary.h"

HashTable ProcessDictionary(Grid DataGrid, char* DictionaryFile)
{
    FILE *file = fopen(DictionaryFile, "r");
    HashTable hash_table = CreateHashTable(DataGrid);
    char word[100];

    while(fgets(word, 100, file))
    {
        word[strlen(word)-1] = 0;    // to remove '\n'
        AddToHashTable(hash_table, word);
    }
    UpdateDataGrid(DataGrid, hash_table);

    fclose(file);

    return hash_table;
}

void UpdateDataGrid(Grid DataGrid, HashTable HashTable)
{
    int i, length;

    for(i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        length = DataGrid->horizontally->coordinates[i].length;
        DataGrid->horizontally->coordinates[i].word_possibilities = HashTable->length[length]->words->size;
    }

    for(i = 0; i < DataGrid->vertically->words_count; i++)
    {
        length = DataGrid->vertically->coordinates[i].length;
        DataGrid->vertically->coordinates[i].word_possibilities = HashTable->length[length]->words->size;
    }
}
