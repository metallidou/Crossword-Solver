#ifndef GRID_STRUCT_H
#define GRID_STRUCT_H

#include <stdbool.h>
#include "../solve/SolveSTRUCT.h"

// visualization
typedef struct GridVISUALIZATION* GridVisual;       
// data
typedef struct GridSTRUCT* Grid;
typedef struct GridHORIZONTALLY* Horizontally;
typedef struct GridVERTICALLY* Vertically;
typedef struct GridLENGTHS* Lengths;                
typedef struct GridCOORDINATES* Coordinates;
typedef struct GridINTERSECTIONS* Intersections;

//-------------------------------------- VISUALIZATION ----------------------------------------------------------------------------------

struct GridVISUALIZATION
{
    int x;                              // width of grid
    int y;                              // height of grid
    bool** IsBlackBox;                  // stores black boxes (we consider black boxes the gaps that can fit no letters)
};

//--------------------------------------- DATA ---------------------------------------------------------------------------------

struct GridSTRUCT                       // the Grid gives information about
{
    Lengths word_lengths;               // the Lengths of the words to be placed
    Horizontally horizontally;          // grid data horizontally
    Vertically vertically;              // grid data vertically
};

struct GridHORIZONTALLY
{
    int words_count;                    // number of words that can fit horizontally
    Coordinates coordinates;            // information about each word's placement horizontally
};

struct GridVERTICALLY
{
    int words_count;                    // number of words that can fit vertically
    Coordinates coordinates;            // information about each word's placement vertically
};

struct GridLENGTHS              
{
    int max_length;                     // the max length of a word that can be placed
    bool* length_exists;                // boolean array that holds all the different lengths between the MinLength and MaxLength
}; 

struct GridCOORDINATES                   
{
    int length;                         // length of word the area can hold
    int word_possibilities;             // number of all possible words that can fit in each gap 
    int start_row;                      // row a gap for a word starts
    int start_col;                      // column a gap for a word starts  
    int end_row;                        // row a gap for a word ends
    int end_col;                        // column a gap for a word ends 
    int flag;                           // indicates the gap priority (for filling the gap)
    Intersections intersections;
    Solution solution;                  // each gap has a solution
};

struct GridINTERSECTIONS
{
    int num;                            // indicates number of gap intersections
    int* gap_index;                      // gaps
};

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------