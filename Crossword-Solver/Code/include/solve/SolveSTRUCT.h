#ifndef SOLVE_STRUCT_H
#define SOLVE_STRUCT_H

#include <stdbool.h>
#include "../vector/VectorSTRUCT.h"

typedef struct CrosswordFLAGS* Flags; 
typedef struct CrosswordSOLUTION* Solution; 
typedef struct CrosswordCONSTRAINTS* Constraints;

typedef char* String;

struct CrosswordFLAGS
{
    bool horizontal_gap;
    int index;
};

struct CrosswordSOLUTION
{
    bool filled;                            // indicates whether a word has been placed in gap
    bool backtracking;                      // indicates whether the gap is a starting point of a backtracking procedure
    String word;                            // word placed in a crossword gap         
    Constraints constraints;                // constraints info
};

struct CrosswordCONSTRAINTS
{
    String letters;                         // constraints a word must have to be placed
    Vector words;                           // list of words with specific constraints
    int used_index;
};

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------