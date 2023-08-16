#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include "../../include/grid/GridData.h"

Grid ProcessGridData(GridVisual VisualGrid)
{
    Grid grid = malloc(sizeof(struct GridSTRUCT)); // Allocate memory for grid
    int x, y, length, max_length;
    x = VisualGrid->x;
    y = VisualGrid->y;

    // Set Max Word Length to grid data structure
    grid->word_lengths = malloc(sizeof(struct GridLENGTHS));
    grid->word_lengths->max_length = max_length = MAX(x, y);
    
    // Before processing the grid, we assume that all word lengths that fit are false
    grid->word_lengths->length_exists = malloc((max_length+1) * sizeof(bool));              

    for (int i = 0; i < max_length; i++)
        grid->word_lengths->length_exists[i] = false;
    
    // Find the Number of Words that fit Horizontally to the grid
    grid->horizontally = malloc(sizeof(struct GridHORIZONTALLY)); 
    grid = NumberWordsFitHorizontally(grid, VisualGrid);
    grid->horizontally->coordinates = malloc(grid->horizontally->words_count * sizeof(struct GridCOORDINATES));

    // Find the Number of Words that fit Vertically to the grid
    grid->vertically = malloc(sizeof(struct GridVERTICALLY)); 
    grid = NumberWordsFitVertically(grid, VisualGrid);
    grid->vertically->coordinates = malloc(grid->vertically->words_count * sizeof(struct GridCOORDINATES));

    // Find the Lengths of the Words that can fit Horizontally
    grid = GapsLengthsHorizontally(grid, VisualGrid);

    // Find the Lengths of the Words that can fit Vertically
    grid = GapLengthsVertically(grid, VisualGrid);

    // Initialize possible Number of Words that can fit Horizontally in each gap
    for (int i = 0; i < grid->horizontally->words_count; i++)
    {
        grid->horizontally->coordinates[i].word_possibilities = 0;
        grid->horizontally->coordinates[i].flag = INT_MIN;
    }

    // Initialize possible Number of Words that can fit Vertically in each gap    
    for (int i = 0; i < grid->vertically->words_count; i++)
    {
        grid->vertically->coordinates[i].word_possibilities = 0;
        grid->vertically->coordinates[i].flag = INT_MIN;
    }
    return grid;
}


Grid NumberWordsFitHorizontally(Grid DataGrid, GridVisual VisualGrid)
{
    int i, j, length, word_count;
    word_count = 0;

    for (i = 0; i < VisualGrid->x; i++)
    {
        length = 0;

        for (j = 0; j < VisualGrid->y; j++)
        {
            if (VisualGrid->IsBlackBox[i][j]) 
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
    DataGrid->horizontally->words_count = word_count;
    return DataGrid;
}

Grid NumberWordsFitVertically(Grid DataGrid, GridVisual VisualGrid)
{
    int i, j, length, word_count = 0;

    for (j = 0; j < VisualGrid->y; j++)
    {
        length = 0;

        for (i = 0; i < VisualGrid->x; i++)
        {
            if (VisualGrid->IsBlackBox[i][j])
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
    DataGrid->vertically->words_count = word_count;
    return DataGrid;;
}

Grid GapsLengthsHorizontally(Grid DataGrid, GridVisual VisualGrid)
{
    int i, j, length, start, end, count = 0;

    for (i = 0; i < VisualGrid->x; i++)
    {
        length = 0;

        for (j = 0; j < VisualGrid->y; j++)
        {
            if (VisualGrid->IsBlackBox[i][j])
            {
                if (length > 1)
                {
                    DataGrid->horizontally->coordinates[count].length = length;
                    DataGrid->horizontally->coordinates[count].start_row = i;
                    DataGrid->horizontally->coordinates[count].start_col = start;
                    DataGrid->horizontally->coordinates[count].end_row = i;
                    DataGrid->horizontally->coordinates[count].end_col = j-1;
                    DataGrid->word_lengths->length_exists[length] = true;
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
            DataGrid->horizontally->coordinates[count].length = length;
            DataGrid->horizontally->coordinates[count].start_row = i;
            DataGrid->horizontally->coordinates[count].start_col = start;
            DataGrid->horizontally->coordinates[count].end_row = i;
            DataGrid->horizontally->coordinates[count].end_col = VisualGrid->y-1;
            DataGrid->word_lengths->length_exists[length] = true;
            count++;
        }
    }
    return DataGrid;
}

Grid GapLengthsVertically(Grid DataGrid, GridVisual VisualGrid)
{
    int i, j, length, start, end, count = 0;

    for (j = 0; j < VisualGrid->y; j++)
    {
        length = 0;

        for (i = 0; i < VisualGrid->x; i++)
        {
            if (VisualGrid->IsBlackBox[i][j])
            {
                if (length > 1)
                {
                    DataGrid->vertically->coordinates[count].length = length;
                    DataGrid->vertically->coordinates[count].start_row = start;
                    DataGrid->vertically->coordinates[count].start_col = j;
                    DataGrid->vertically->coordinates[count].end_row = i-1;
                    DataGrid->vertically->coordinates[count].end_col = j;
                    DataGrid->word_lengths->length_exists[length] = true;
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
            DataGrid->vertically->coordinates[count].length = length;
            DataGrid->vertically->coordinates[count].start_row = start;
            DataGrid->vertically->coordinates[count].start_col = j;
            DataGrid->vertically->coordinates[count].end_row = VisualGrid->x-1;
            DataGrid->vertically->coordinates[count].end_col = j;
            DataGrid->word_lengths->length_exists[length] = true;
            count++;
        }
    }
    return DataGrid;
}
