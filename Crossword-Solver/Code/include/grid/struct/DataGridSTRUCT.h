#pragma once

#include <stdbool.h>
#include "../../vector/struct/VectorSTRUCT.h"

typedef char* String;      

typedef struct DataGridSTRUCT DataGrid;
typedef struct HorizontallySTRUCT Horizontally;
typedef struct VerticallySTRUCT Vertically;
typedef struct LengthsSTRUCT Lengths;                
typedef struct CoordinatesSTRUCT Coordinates;
typedef struct IntersectionsSTRUCT Intersections;

struct DataGridSTRUCT                   
{
    Lengths* word_lengths;               // the Lengths of the words to be placed
    Horizontally* horizontally;          // data horizontally
    Vertically* vertically;              // data vertically
};

struct HorizontallySTRUCT
{
    int dimensions;                     // horizontal dimension of crossword
    int words_count;                    // number of words that can fit horizontally
    Coordinates* gap;                   // information about each word's placement horizontally
};

struct VerticallySTRUCT
{
    int dimensions;                     // vertical dimension of crossword
    int words_count;                    // number of words that can fit vertically
    Coordinates* gap;                   // information about each word's placement vertically
};

struct LengthsSTRUCT              
{
    int max;                     // the max length of a word that can be placed
    bool* exists;                // boolean array that holds all the different lengths between the MinLength and MaxLength
}; 

struct CoordinatesSTRUCT             
{
    int length;                         // length of word the area can hold
    int start_row;                      // row a gap for a word starts
    int start_col;                      // column a gap for a word starts  
    int end_row;                        // row a gap for a word ends
    int end_col;                        // column a gap for a word ends 
    int flag;                           // indicates the gap priority (for filling the gap)
    bool filled;                        // true when gap is filled with a word
    int index;                          // gap index
    String word;                        // word placed as a solution
    String constraints;                 // constraints created by other word placements
    Vector* words_vector;               // word choices that fit several criteria
    Intersections* intersections;       // information about the gap's intersections with other words
};

struct IntersectionsSTRUCT
{
    int num;                            // indicates number of gap intersections
    int* gap_index;                     // index array of intersected gaps
};
