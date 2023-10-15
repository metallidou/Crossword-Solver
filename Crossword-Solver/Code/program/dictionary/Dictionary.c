#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/dictionary/Dictionary.h"

HashTable ProcessDictionary(DataGrid DataGrid, char* DictionaryFile)
{
    // open dictionary file
    FILE *file = fopen(DictionaryFile, "r");

    // initialize hash table
    HashTable hash_table = CreateHashTable(DataGrid);
    // word is used for reading each file line 
    char* word = malloc(100 * sizeof(char));

    // get line input
    while(fgets(word, 100, file))                   
    {
        // to remove '\n'
        word[strlen(word)-1] = 0;                   

        // if appropriate add to hash table
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

    // if length of word bigger than crossword limit
    if (length > DataGrid.word_lengths->max)            
        return false;

    // if length of word cannot be included to crossword
    if (DataGrid.word_lengths->exists[length] == false)
        return false;
    
    return true;
}

