#ifndef DATA_GRID_STRUCT_H
#define DATA_GRID_STRUCT_H

#include <stdbool.h>
#include "../vector/VectorSTRUCT.h"

typedef char* String;      

// data grid
typedef struct DataGridSTRUCT DataGrid;
typedef struct HorizontallySTRUCT Horizontally;
typedef struct VerticallySTRUCT Vertically;
typedef struct LengthsSTRUCT Lengths;                
typedef struct CoordinatesSTRUCT Coordinates;
typedef struct IntersectionsSTRUCT Intersections;

//--------------------------------------- DATA GRID ---------------------------------------------------------------------------------

struct DataGridSTRUCT                   // the Grid gives information about
{
    Lengths* word_lengths;               // the Lengths of the words to be placed
    Horizontally* horizontally;          // grid data horizontally
    Vertically* vertically;              // grid data vertically
};

struct HorizontallySTRUCT
{
    int words_count;                    // number of words that can fit horizontally
    Coordinates* gap;                   // information about each word's placement horizontally
};

struct VerticallySTRUCT
{
    int words_count;                    // number of words that can fit vertically
    Coordinates* gap;                  // information about each word's placement vertically
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
    bool filled;
    int index;
    String word;
    String constraints;
    Vector* words_vector;
    Intersections* intersections;
};

struct IntersectionsSTRUCT
{
    int num;                            // indicates number of gap intersections
    int* gap_index;                     // gaps
};

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------