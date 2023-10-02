#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include "../../include/grid/DataGrid.h"

#define MAX(x,y) ((x) ? (y) : (x) > (y))

DataGrid ProcessDataGrid(VisualGrid VisualGrid)
{
    DataGrid grid;
    int x, y, length, max_length;

    x = VisualGrid.x;       // width
    y = VisualGrid.y;       // height

    // set max word length 
    grid.word_lengths = malloc(sizeof(Lengths));
    grid.word_lengths->max = max_length = MAX(x, y);
    
    // before processing the grid, we assume that all word lengths that fit are false
    grid.word_lengths->exists = malloc((max_length+1) * sizeof(bool));              
   
    for (int i = 0; i <= max_length; i++)
        grid.word_lengths->exists[i] = false;
    
    // get number of words that fit horizontally to the grid
    grid.horizontally = malloc(sizeof(Horizontally));
    grid.horizontally->dimensions = x;                      // set width 
    grid = NumberWordsFitHorizontally(grid, VisualGrid);
    grid.horizontally->gap = malloc(grid.horizontally->words_count * sizeof(Coordinates));

    // get number of words that fit vertically to the grid
    grid.vertically = malloc(sizeof(Vertically)); 
    grid.vertically->dimensions = y;                        // set height
    grid = NumberWordsFitVertically(grid, VisualGrid);
    grid.vertically->gap = malloc(grid.vertically->words_count * sizeof(Coordinates));

    // declare lengths of the words that can fit horizontally
    grid = GapsLengthsHorizontally(grid, VisualGrid);

    // declare lengths of the words that can fit vertically
    grid = GapLengthsVertically(grid, VisualGrid);

    // initialize possible number of words that can fit horizontally in each gap
    for (int i = 0; i < grid.horizontally->words_count; i++)
        grid.horizontally->gap[i].flag = INT_MIN;

    // initialize possible number of words that can fit vertically in each gap  
    for (int i = 0; i < grid.vertically->words_count; i++)
        grid.vertically->gap[i].flag = INT_MIN;
    
    return grid;
}


DataGrid NumberWordsFitHorizontally(DataGrid DataGrid, VisualGrid VisualGrid)
{
    int i, j, length, word_count;
    word_count = 0;

    for (i = 0; i < VisualGrid.x; i++)
    {
        length = 0;
        for (j = 0; j < VisualGrid.y; j++)
        {
            if (VisualGrid.black_box[i][j])         // when meeting a black box 
            {   
                if (length > 1)                     // that means we had encountered a gap that can fit a words
                    word_count++;                   // we assume that strings of length 1 are not words
                length = 0;                         // initialize length for next time
                continue;
            }
            length++;                               // if no black box, then we have a word gap
        }
        if (length > 1)                             // same thing but at the end of line
            word_count++;
    }
    DataGrid.horizontally->words_count = word_count;    // store value
    return DataGrid;
}

DataGrid NumberWordsFitVertically(DataGrid DataGrid, VisualGrid VisualGrid)
{
    int i, j, length, word_count = 0;

    for (j = 0; j < VisualGrid.y; j++)
    {
        length = 0;
        for (i = 0; i < VisualGrid.x; i++)      // when meeting a black box 
        {
            if (VisualGrid.black_box[i][j])
            {   
                if (length > 1)                 // that means we had encountered a gap that can fit a words  
                    word_count++;
                length = 0;                     // initialize length for next time
                continue;
            }
            length++;                           // if no black box, then we have a word gap
        }
        if (length > 1)                         // same thing but at the end of column
            word_count++;
    }
    DataGrid.vertically->words_count = word_count;  // store value
    return DataGrid;
}

DataGrid GapsLengthsHorizontally(DataGrid DataGrid, VisualGrid VisualGrid)
{
    int i, j, length, start, end, count = 0;

    for (i = 0; i < VisualGrid.x; i++)
    {
        length = 0;    
        for (j = 0; j < VisualGrid.y; j++)
        {
            if (VisualGrid.black_box[i][j])
            {
                if (length > 1)     // we have detected a word
                {
                    DataGrid.horizontally->gap[count].length = length;          // assign length
                    DataGrid.horizontally->gap[count].start_row = i;            // start row
                    DataGrid.horizontally->gap[count].start_col = start;        // start column
                    DataGrid.horizontally->gap[count].end_row = i;              // end row
                    DataGrid.horizontally->gap[count].end_col = j-1;            // end column
                    DataGrid.word_lengths->exists[length] = true;               // declare that word length exists
                    count++;
                }
                length = 0;         // initialize
                continue;
            }
            if (length == 0)        // hold the start position of a potential word
                start = j;
            length++;               
        }
        if (length > 1)             // same thing but for the end of the row
        {
            DataGrid.horizontally->gap[count].length = length;
            DataGrid.horizontally->gap[count].start_row = i;
            DataGrid.horizontally->gap[count].start_col = start;
            DataGrid.horizontally->gap[count].end_row = i;
            DataGrid.horizontally->gap[count].end_col = VisualGrid.y-1;
            DataGrid.word_lengths->exists[length] = true;
            count++;
        }
    }
    return DataGrid;
}

DataGrid GapLengthsVertically(DataGrid DataGrid, VisualGrid VisualGrid)
{
    int i, j, length, start, end, count = 0;

    for (j = 0; j < VisualGrid.y; j++)
    {
        length = 0;
        for (i = 0; i < VisualGrid.x; i++)
        {
            if (VisualGrid.black_box[i][j])
            {
                if (length > 1)         // we have detected a word
                {
                    DataGrid.vertically->gap[count].length = length;                // length
                    DataGrid.vertically->gap[count].start_row = start;              // start row
                    DataGrid.vertically->gap[count].start_col = j;                  // start column
                    DataGrid.vertically->gap[count].end_row = i-1;                  // end row
                    DataGrid.vertically->gap[count].end_col = j;                    // end column
                    DataGrid.word_lengths->exists[length] = true;                   // declare that word length exists
                    count++;
                }
                length = 0;         // initialize
                continue;
            }
            if (length == 0)        
                start = i;          // hold the start position of a potential word
            length++;
        }
        if (length > 1)             // same thing but for the end of the column
        {
            DataGrid.vertically->gap[count].length = length;
            DataGrid.vertically->gap[count].start_row = start;
            DataGrid.vertically->gap[count].start_col = j;
            DataGrid.vertically->gap[count].end_row = VisualGrid.x-1;
            DataGrid.vertically->gap[count].end_col = j;
            DataGrid.word_lengths->exists[length] = true;
            count++;
        }
    }
    return DataGrid;
}

void FreeDataGrid(DataGrid* DataGrid)
{
    for (int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        free(DataGrid->horizontally->gap[i].intersections->gap_index);
        free(DataGrid->horizontally->gap[i].intersections);
        free(DataGrid->horizontally->gap[i].constraints);
        free(DataGrid->horizontally->gap[i].word);
    }
    free(DataGrid->horizontally->gap);
    free(DataGrid->horizontally);
    
    for (int i = 0; i < DataGrid->vertically->words_count; i++)
    {
        free(DataGrid->vertically->gap[i].intersections->gap_index);
        free(DataGrid->vertically->gap[i].intersections);
        free(DataGrid->vertically->gap[i].constraints);
        free(DataGrid->vertically->gap[i].word);
    }
    free(DataGrid->vertically->gap);
    free(DataGrid->vertically);

    free(DataGrid->word_lengths->exists);
    free(DataGrid->word_lengths);
}