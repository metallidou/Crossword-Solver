#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/dictionary/Dictionary.h"

HashTable ProcessDictionary(DataGrid DataGrid, char* DictionaryFile)
{
    FILE *file = fopen(DictionaryFile, "r");

    HashTable hash_table = CreateHashTable(DataGrid);
    char* word = malloc(100 * sizeof(char));

    while(fgets(word, 100, file))
    {
        word[strlen(word)-1] = 0;               // to remove '\n'

        if (IsWithinBounds(DataGrid, word)) 
            AddToHashTable(&hash_table, word);
    }
    free(word);
    fclose(file);

    return hash_table;
}

bool IsWithinBounds(DataGrid DataGrid, String Word)
{
    int length = strlen(Word);

    if (length > DataGrid.word_lengths->max)
        return false;

    if (DataGrid.word_lengths->exists[length] == false)
        return false;
    
    return true;
}

