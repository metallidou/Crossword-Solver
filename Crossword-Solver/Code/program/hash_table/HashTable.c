#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/hash_table/HashTable.h"

HashTable CreateHashTable(DataGrid DataGrid)
{
    HashTable hash_table;
    int i, j, k, max_length;
    
    // max length a word can have
    max_length = DataGrid.word_lengths->max;            
    hash_table.max_length = max_length;

    // memory allocation to store word lengths
    hash_table.length = malloc((max_length+1) * sizeof(HashTableLength));

    // initialize each vector that will store words of specific lengths
    for(i = 0; i <= max_length; i++)
        hash_table.length[i].words = VectorInitialize();
    
    // memory allocation to store letter positions, words of different lengths can have 
    for(i = 0; i <= max_length; i++)
        hash_table.length[i].position = malloc((i+1) * sizeof(HashTablePosition));   

    // memory allocation to store all different letters, on each position, for each word length  
    for(i = 0; i <= max_length; i++)
    {
        for(j = 0; j <= i; j++)
        {
            hash_table.length[i].position[j].letter = malloc(26 * sizeof(HashTableLetter));
            for(k = 0; k < 26; k++)
                hash_table.length[i].position[j].letter[k].words = VectorInitialize();      // vector initialization for storing words
        }
    }    
    return hash_table;
}

void AddToHashTable(HashTable* HashTable, char* Word)
{
    int index, length;
    length = strlen(Word);

    // inserts the word to the corresponding words vector of hash table
    VectorInsert(&(HashTable->length[length].words), Word);     

    for(int i = 0; i < length; i++)
    {
        // the index takes values from 0 up to 25
        index = Word[i] - 'a';      
        VectorInsert(&(HashTable->length[length].position[i].letter[index].words), Word);
    }
}

void FreeHashTable(HashTable* HashTable)
{
    for (int i = 0; i <= HashTable->max_length; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            for (int k = 0; k < 26; k++)
                FreeVector(&(HashTable->length[i].position[j].letter[k].words));
            free(HashTable->length[i].position[j].letter);
        }
        FreeVector((&HashTable->length[i].words));
        free(HashTable->length[i].position);
    }
    free(HashTable->length);   
}