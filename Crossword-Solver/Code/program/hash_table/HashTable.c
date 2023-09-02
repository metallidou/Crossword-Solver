#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/hash_table/HashTable.h"

HashTable CreateHashTable(DataGrid DataGrid)
{
    int i, j, k, max_length;
    
    // max length a word can have
    max_length = DataGrid.word_lengths->max;            

    // memory allocation for hash table
    HashTable hash_table;  

    // memory allocation to store word lengths
    hash_table.max_length = max_length;
    hash_table.length = malloc((max_length+1) * sizeof(HashTableLength));

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
                hash_table.length[i].position[j].letter[k].words = VectorInitialize();
        }
    }    
    return hash_table;
}

void AddToHashTable(HashTable* HashTable, char* Word)
{
    int index, length;
    length = strlen(Word);

    VectorInsert(&(HashTable->length[length].words), Word);

    for(int i = 0; i < length; i++)
    {
        index = Word[i] - 'a';
        VectorInsert(&(HashTable->length[length].position[i].letter[index].words), Word);
    }
}