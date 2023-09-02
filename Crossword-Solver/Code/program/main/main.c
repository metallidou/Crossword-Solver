#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/grid/VisualGrid.h"
#include "../../include/grid/DataGrid.h"
#include "../../include/dictionary/Dictionary.h"
#include "../../include/hash_table/HashTable.h"
#include "../../include/solve/Solve.h"

char** VisualizeResult(DataGrid DataGrid, VisualGrid VisualGrid);
void PrintResult(char** ResultTable, int X, int Y);

int main(int argc, char** argv)
{
    VisualGrid visual_grid;
    DataGrid data_grid;
    HashTable hash_table;

    visual_grid = CreateVisualGrid(argv[1]);
    data_grid = ProcessDataGrid(visual_grid);
    hash_table = ProcessDictionary(data_grid, argv[2]);

    Solve(&data_grid, hash_table);

    PrintResult(VisualizeResult(data_grid, visual_grid), visual_grid.x, visual_grid.y);
       
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
    

    for(int i = 0; i < DataGrid.horizontally->words_count; i++)
    {
        printf("length %d row %d horizontally %s flag %d ", DataGrid.horizontally->gap[i].length, DataGrid.horizontally->gap[i].start_row, DataGrid.horizontally->gap[i].word, DataGrid.horizontally->gap[i].flag);
        if(DataGrid.horizontally->gap[i].constraints)
        {
            printf("constraints ");

            for(int k = 0; k < DataGrid.horizontally->gap[i].length; k++)
            {
                if(DataGrid.horizontally->gap[i].constraints[k] != ' ')
                    printf("%c", DataGrid.horizontally->gap[i].constraints[k]);
                else
                    printf("*");
            }
            printf("\n");  
        }
        else
            printf("no constraints\n");    
    }
    for(int j = 0; j < DataGrid.vertically->words_count; j++)
    {
        printf("length %d col %d vertically %s flag %d ", DataGrid.vertically->gap[j].length, DataGrid.vertically->gap[j].start_col, DataGrid.vertically->gap[j].word, DataGrid.vertically->gap[j].flag);
        if(DataGrid.vertically->gap[j].constraints)
        {
            printf("constraints ");
            for(int k = 0; k < DataGrid.vertically->gap[j].length; k++)
            {
                if(DataGrid.vertically->gap[j].constraints[k] != ' ')
                    printf("%c", DataGrid.vertically->gap[j].constraints[k]);
                else
                    printf("*");
            }
            printf("\n");    
        }
        else
            printf("no constraints\n");   
    }
    return result;
}

void PrintResult(char** ResultTable, int X, int Y)
{
    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j <Y; j++)
        {
            if(ResultTable[i][j] == '#')
                printf("###");
            else    
                printf(" %c ", ResultTable[i][j]);
        }
        printf("\n");    
    }
    printf("\n");
}