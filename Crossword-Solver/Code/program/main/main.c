#include <stdio.h>
#include <stdlib.h>
#include "../../include/grid/GridVisualization.h"
#include "../../include/grid/GridData.h"
#include "../../include/dictionary/Dictionary.h"
#include "../../include/hash_table/HashTable.h"
#include "../../include/solve/Solve.h"

char** VisualizeResult(Grid DataGrid, GridVisual VisualGrid);
void PrintResult(char** ResultTable, int X, int Y);

int main(int argc, char** argv)
{
    GridVisual visual_grid;
    Grid data_grid;
    HashTable dictionary;

    visual_grid = CreateGridVisualization(argv[1]);
    data_grid = ProcessGridData(visual_grid);
    dictionary = ProcessDictionary(data_grid, argv[2]);
    data_grid = Solve(data_grid, dictionary);

    PrintResult(VisualizeResult(data_grid, visual_grid), visual_grid->x, visual_grid->y);
       
/*
    printf("words horizontally %d\n", data_grid->horizontally->words_count);
    printf("words vertically %d\n", data_grid->vertically->words_count);

    printf("horizontally\n");
    for(int i = 0; i < data_grid->horizontally->words_count; i++)
        printf("length %d start_row %d end_row %d start_col %d end_col %d possibilities %d\n", data_grid->horizontally->coordinates[i].length, data_grid->horizontally->coordinates[i].start_row, data_grid->horizontally->coordinates[i].end_row, data_grid->horizontally->coordinates[i].start_col, data_grid->horizontally->coordinates[i].end_col, data_grid->horizontally->coordinates[i].word_possibilities);
    printf("vertically\n");
    for(int i = 0; i < data_grid->vertically->words_count; i++)
        printf("length %d start_row %d end_row %d start_col %d end_col %d possibilities %d\n", data_grid->vertically->coordinates[i].length, data_grid->vertically->coordinates[i].start_row, data_grid->vertically->coordinates[i].end_row, data_grid->vertically->coordinates[i].start_col, data_grid->vertically->coordinates[i].end_col, data_grid->vertically->coordinates[i].word_possibilities);

    for(int i = 0; i <= data_grid->word_lengths->max_length; i++)
    {
        if(data_grid->word_lengths->length_exists[i] == true)
            printf("length %d exists and words number is %d\n", i, dictionary->length[i]->words_num);
    }
    printf("\n");

    printf("  ");
    for(int i = 0; i < visual_grid->x; i++)
        printf(" %d ", i);
    printf("\n");    

    int c = 0;

    for(int i = 0; i < visual_grid->x; i++)
    {
        for(int j = 0; j < visual_grid->y; j++)
        {
            if(j == 0)
            {
                printf(" %d\t", c);
                c++;
            }
            if(visual_grid->IsBlackBox[i][j])
                printf("###");
            else
                printf(" - ");    
        }
        printf("\n");
    }
*/
    return 0;
}

char** VisualizeResult(Grid DataGrid, GridVisual VisualGrid)
{
    int temp, row;
    char** result;

    // memory allocation for result table
    result = malloc((VisualGrid->x) * sizeof(char*));
    for(int i = 0; i < VisualGrid->x; i++)
        result[i] = malloc((VisualGrid->y) * sizeof(char));

    // initialize table with result
    for(int i = 0; i < VisualGrid->x; i++)
    {
        for(int j = 0; j < VisualGrid->y; j++)
        {   
            if(VisualGrid->IsBlackBox[i][j])
                result[i][j] = '#';
        }
    }

    // place words on result table
    for(int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        row = DataGrid->horizontally->coordinates[i].start_row;
        temp = DataGrid->horizontally->coordinates[i].start_col;
        
        for(int j = 0; j < DataGrid->horizontally->coordinates[i].length; j++)
        {
            if(DataGrid->horizontally->coordinates[i].solution->filled == true) 
                result[row][temp+j] = DataGrid->horizontally->coordinates[i].solution->word[j];
            else
                result[row][temp+j] = '+';
        }
    }

    for(int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        printf("row %d horizontally %s flag %d ", DataGrid->horizontally->coordinates[i].start_row, DataGrid->horizontally->coordinates[i].solution->word, DataGrid->horizontally->coordinates[i].flag);
        if(DataGrid->horizontally->coordinates[i].solution->constraints)
        {
            printf("constraints ");

            for(int k = 0; k < DataGrid->horizontally->coordinates[i].length; k++)
            {
                if(DataGrid->horizontally->coordinates[i].solution->constraints->letters[k] != ' ')
                    printf("%c", DataGrid->horizontally->coordinates[i].solution->constraints->letters[k]);
                else
                    printf("*");
            }
            printf("\n");  
        }
        else
            printf("no constraints\n");    
    }
    for(int j = 0; j < DataGrid->vertically->words_count; j++)
    {
        printf("col %d vertically %s flag %d ", DataGrid->vertically->coordinates[j].start_col, DataGrid->vertically->coordinates[j].solution->word, DataGrid->vertically->coordinates[j].flag);
        if(DataGrid->vertically->coordinates[j].solution->constraints)
        {
            printf("constraints ");
            for(int k = 0; k < DataGrid->vertically->coordinates[j].length; k++)
            {
                if(DataGrid->vertically->coordinates[j].solution->constraints->letters[k] != ' ')
                    printf("%c", DataGrid->vertically->coordinates[j].solution->constraints->letters[k]);
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
