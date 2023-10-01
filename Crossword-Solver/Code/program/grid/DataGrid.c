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

    // Set Max Word Length to grid data structure
    grid.word_lengths = malloc(sizeof(Lengths));
    grid.word_lengths->max = max_length = MAX(x, y);
    
    // Before processing the grid, we assume that all word lengths that fit are false
    grid.word_lengths->exists = malloc((max_length+1) * sizeof(bool));              

    for (int i = 0; i <= max_length; i++)
        grid.word_lengths->exists[i] = false;
    
    // Find the Number of Words that fit Horizontally to the grid
    grid.horizontally = malloc(sizeof(Horizontally));
    grid.horizontally->dimensions = x; 
    grid = NumberWordsFitHorizontally(grid, VisualGrid);
    grid.horizontally->gap = malloc(grid.horizontally->words_count * sizeof(Coordinates));

    // Find the Number of Words that fit Vertically to the grid
    grid.vertically = malloc(sizeof(Vertically)); 
    grid.vertically->dimensions = y;
    grid = NumberWordsFitVertically(grid, VisualGrid);
    grid.vertically->gap = malloc(grid.vertically->words_count * sizeof(Coordinates));

    // Find the Lengths of the Words that can fit Horizontally
    grid = GapsLengthsHorizontally(grid, VisualGrid);

    // Find the Lengths of the Words that can fit Vertically
    grid = GapLengthsVertically(grid, VisualGrid);

    // Initialize possible Number of Words that can fit Horizontally in each gap
    for (int i = 0; i < grid.horizontally->words_count; i++)
        grid.horizontally->gap[i].flag = INT_MIN;

    // Initialize possible Number of Words that can fit Vertically in each gap    
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
            if (VisualGrid.black_box[i][j]) 
            {   
                if (length > 1)                
                    word_count++;
                length = 0;
                continue;
            }
            length++;
        }
        if (length > 1)
            word_count++;
    }
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
            if (VisualGrid.black_box[i][j])
            {   
                if (length > 1)               
                    word_count++;
                length = 0;
                continue;
            }
            length++;
        }
        if (length > 1)
            word_count++;
    }
    DataGrid.vertically->words_count = word_count;
    return DataGrid;;
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
            if (length == 0)
                start = j;
            length++;
        }
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
            if (length == 0)
                start = i;
            length++;
        }
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