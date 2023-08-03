#ifndef HASH_TABLE_STRUCT_H
#define HASH_TABLE_STRUCT_H

#include "../grid/GridSTRUCT.h"
#include "../vector/VectorSTRUCT.h"

// hash table
typedef struct HashTableSTRUCT* HashTable;
typedef struct HashTableLENGTH* HashTableLength; 
typedef struct HashTablePOSITION* HashTablePosition;
typedef struct HashTableLETTER* HashTableLetter;

//-------------------------------------- HASH TABLE ----------------------------------------------------------------------------------

struct HashTableSTRUCT
{
    int max_length;
    HashTableLength* length;
};

struct HashTableLENGTH
{
    Vector words;
    HashTablePosition* position;
};

struct HashTablePOSITION
{
    HashTableLetter* letter;
};

struct HashTableLETTER
{
    Vector words;
};

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------