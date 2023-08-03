#ifndef SOLVE_STRUCT_H
#define SOLVE_STRUCT_H

#include <stdbool.h>
#include "../vector/VectorSTRUCT.h"
#include "../queue/QueueSTRUCT.h"

typedef struct CrosswordFLAGS* Flags; 
typedef struct CrosswordSOLUTION* Solution; 
typedef struct CrosswordCONSTRAINTS* Constraints;
typedef struct Crossword_NO_CONSTRAINTS* NoConstraints;

struct CrosswordFLAGS
{
    bool horizontal_gap;
    int index;
};

struct CrosswordSOLUTION
{
    bool filled;                        // indicates whether a word has been placed in gap
    bool backtracking;                  // indicates whether the gap is a starting point of a backtracking procedure
    char* word_placed;                  // word placed in a crossword gap         

    bool constraints;                   // indicates whether a gap has constraints
    Constraints has_constraints;        // if constraints
    NoConstraints no_constraints;       // if no constraints
};

struct CrosswordCONSTRAINTS
{
    bool* constrained_letter;           // true if a letter must be specific
    char* constraints;                  // constraints a word must have to be placed
    Vector words;                        // list of words with specific constraints
};

struct Crossword_NO_CONSTRAINTS
{
    int used_index;                     // index of word used in vector
    Vector words;                       // vector of words that can be placed
};

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------