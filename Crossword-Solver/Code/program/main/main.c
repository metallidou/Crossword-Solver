#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/grid/VisualGrid.h"
#include "../../include/grid/DataGrid.h"
#include "../../include/dictionary/Dictionary.h"
#include "../../include/hash_table/HashTable.h"
#include "../../include/solve/Solve.h"

extern bool SOLUTION;

char** VisualizeResult(DataGrid DataGrid, VisualGrid VisualGrid);
void PrintResult(DataGrid DataGrid, VisualGrid VisualGrid);

int main(int argc, char** argv)
{
    VisualGrid visual_grid;
    DataGrid data_grid;
    HashTable hash_table;

    visual_grid = CreateVisualGrid(argv[1]);
    data_grid = ProcessDataGrid(visual_grid);
    hash_table = ProcessDictionary(data_grid, argv[2]);

    Solve(&data_grid, hash_table);
    PrintResult(data_grid, visual_grid);

    return 0;
}

char** VisualizeResult(DataGrid DataGrid, VisualGrid VisualGrid)
{
    int temp, row, col;
    char** result;

    // memory allocation for result table
    result = malloc((VisualGrid.x) * sizeof(char*));
    for(int i = 0; i < VisualGrid.x; i++)
        result[i] = malloc((VisualGrid.y) * sizeof(char));

    // initialize table with result
    for(int i = 0; i < VisualGrid.x; i++)
    {
        for(int j = 0; j < VisualGrid.y; j++)
        {   
            if(VisualGrid.black_box[i][j])
                result[i][j] = '#';
        }
    }

    // place words on result table
    for(int i = 0; i < DataGrid.horizontally->words_count; i++)
    {
        row = DataGrid.horizontally->gap[i].start_row;
        temp = DataGrid.horizontally->gap[i].start_col;
        
        for(int j = 0; j < DataGrid.horizontally->gap[i].length; j++)
        {
            if(DataGrid.horizontally->gap[i].filled == true) 
                result[row][temp+j] = DataGrid.horizontally->gap[i].word[j];
            else
              result[row][temp+j] = '+';
        }
    }

    for(int i = 0; i < DataGrid.vertically->words_count; i++)
    {
        col = DataGrid.vertically->gap[i].start_col;
        temp = DataGrid.vertically->gap[i].start_row;
        
        for(int j = 0; j < DataGrid.vertically->gap[i].length; j++)
        {
            if(DataGrid.vertically->gap[i].filled == true) 
                result[temp+j][col] = DataGrid.vertically->gap[i].word[j];
        }
    }
    return result;
}

void PrintResult(DataGrid DataGrid, VisualGrid VisualGrid)
{
    int black = 0;

    if (SOLUTION)
    {
        char** result = VisualizeResult(DataGrid, VisualGrid);

        for(int i = 0; i < VisualGrid.x; i++)
        {
            for(int j = 0; j < VisualGrid.y; j++)
            {
                if(result[i][j] == '#')
                {
                    printf("###");
                    black++;
                }
                else    
                    printf(" %c ", result[i][j]);
            }
            printf("\n");    
        }
        printf("\n");
    }
    else
        printf("CROSSWORD CANNOT BE SOLVED!\n");
}