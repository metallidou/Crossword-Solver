#pragma once

#include "../../grid/struct/DataGridSTRUCT.h"
#include "../../vector/struct/VectorSTRUCT.h"

typedef struct HashTableSTRUCT HashTable;
typedef struct HashTableLENGTH HashTableLength; 
typedef struct HashTablePOSITION HashTablePosition;
typedef struct HashTableLETTER HashTableLetter;

struct HashTableSTRUCT
{
    int max_length;                         // max length of stored words
    HashTableLength* length;                // length 
};

struct HashTableLENGTH
{
    Vector words;                           // vector of words of a specific length only (for ease of search)
    HashTablePosition* position;            // position of a word with specific length
};

struct HashTablePOSITION
{
    HashTableLetter* letter;                // letter in a position of a word with specific length
};

struct HashTableLETTER
{
    Vector words;                           // vector of words with the above criteria
};
