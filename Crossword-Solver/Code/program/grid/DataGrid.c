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

    x = VisualGrid.x;       
    y = VisualGrid.y;       

    // set max word length 
    grid.word_lengths = malloc(sizeof(Lengths));
    grid.word_lengths->max = max_length = MAX(x, y);
    
    // before processing the grid, we assume that all word lengths that fit are false
    grid.word_lengths->exists = malloc((max_length+1) * sizeof(bool));              
    for (int i = 0; i <= max_length; i++)
        grid.word_lengths->exists[i] = false;
    
    // set width
    grid.horizontally = malloc(sizeof(Horizontally));
    grid.horizontally->dimensions = x;                       
    
    // get number of words that fit horizontally to the grid
    grid = NumberWordsFitHorizontally(grid, VisualGrid);

    // set height
    grid.vertically = malloc(sizeof(Vertically)); 
    grid.vertically->dimensions = y;                        
    
    // get number of words that fit vertically to the grid
    grid = NumberWordsFitVertically(grid, VisualGrid);

    // declare lengths of the words that can fit horizontally
    grid.horizontally->gap = malloc(grid.horizontally->words_count * sizeof(Coordinates));
    grid = GapsLengthsHorizontally(grid, VisualGrid);

    // declare lengths of the words that can fit vertically
    grid.vertically->gap = malloc(grid.vertically->words_count * sizeof(Coordinates));
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
            // when meeting a black box
            if (VisualGrid.black_box[i][j])          
            {   
                // that means we have encountered a gap that can fit a words
                // we assume that strings of length 1 are not words
                if (length > 1)                     
                    word_count++;                   
                
                length = 0;                       
                continue;
            }
            // if no black box, then we have a word gap
            length++;                               
        }
        // same thing but at the end of line
        if (length > 1)                             
            word_count++;
    }
     // store value
    DataGrid.horizontally->words_count = word_count;   
    
    return DataGrid;
}

DataGrid NumberWordsFitVertically(DataGrid DataGrid, VisualGrid VisualGrid)
{
    int i, j, length, word_count = 0;

    for (j = 0; j < VisualGrid.y; j++)
    {
        length = 0;
        for (i = 0; i < VisualGrid.x; i++)       
        {
            // when meeting a black box
            if (VisualGrid.black_box[i][j])
            {
                // that means we had encountered a gap that can fit a words   
                if (length > 1)                   
                    word_count++;
                
                length = 0;                     
                continue;
            }
            // if no black box, then we have a word gap
            length++;                           
        }
        // same thing but at the end of column
        if (length > 1)                         
            word_count++;
    }
    // store value
    DataGrid.vertically->words_count = word_count;  
    
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
                // we have detected a word
                if (length > 1)     
                {
                    DataGrid.horizontally->gap[count].length = length;          
                    DataGrid.horizontally->gap[count].start_row = i;            
                    DataGrid.horizontally->gap[count].start_col = start;        
                    DataGrid.horizontally->gap[count].end_row = i;              
                    DataGrid.horizontally->gap[count].end_col = j-1;            
                    DataGrid.word_lengths->exists[length] = true;               
                    count++;
                }
                length = 0;  
                continue;
            }
            // hold the start position of a potential word
            if (length == 0)        
                start = j;

            length++;               
        }
        // same thing but for the end of the row
        if (length > 1)             
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
                // we have detected a word
                if (length > 1)         
                {
                    DataGrid.vertically->gap[count].length = length;                
                    DataGrid.vertically->gap[count].start_row = start;              
                    DataGrid.vertically->gap[count].start_col = j;                  
                    DataGrid.vertically->gap[count].end_row = i-1;                  
                    DataGrid.vertically->gap[count].end_col = j;                    
                    DataGrid.word_lengths->exists[length] = true;                   
                    count++;
                }
                length = 0;  
                continue;
            }
            // hold the start position of a potential word
            if (length == 0)        
                start = i;          
                
            length++;
        }
        // same thing but for the end of the column
        if (length > 1)             
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