#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/grid/VisualGrid.h"
#include "../../include/grid/DataGrid.h"
#include "../../include/dictionary/Dictionary.h"
#include "../../include/hash_table/HashTable.h"
#include "../../include/solve/Solve.h"

// declares whether the crossword can be solved
extern bool SOLUTION;       

// apply result to a char table
char** VisualizeResult(DataGrid DataGrid, VisualGrid VisualGrid);
// print the contents of the char table as result
void PrintResult(DataGrid DataGrid, VisualGrid VisualGrid);
// free memory
void FreeResultTable(char** ResultTable, int Width);

int main(int argc, char** argv)
{
    VisualGrid visual_grid;             
    DataGrid data_grid;
    HashTable hash_table;

    // read the crossword file and create a struct containing its visual complonents
    visual_grid = CreateVisualGrid(argv[1]);                
    // analyse further the visual grid and get information about the solution coordinates
    data_grid = ProcessDataGrid(visual_grid);               
    // analyse the dictionary file and create a hash table, for search purposes 
    hash_table = ProcessDictionary(data_grid, argv[2]);     

    // attempts to solve crossword
    Solve(&data_grid, hash_table);                          
    // prints final result
    PrintResult(data_grid, visual_grid);                    

    FreeDataGrid(&data_grid);
    FreeVisualGrid(&visual_grid);
    FreeHashTable(&hash_table);

    return 0;
}

char** VisualizeResult(DataGrid DataGrid, VisualGrid VisualGrid)
{
    int temp, row, col;
    char** result;

    // initialization of char table
    result = malloc((VisualGrid.x) * sizeof(char*));
    for(int i = 0; i < VisualGrid.x; i++)
        result[i] = malloc((VisualGrid.y) * sizeof(char));

    // black boxes are symbolized as '#'
    for(int i = 0; i < VisualGrid.x; i++)
    {
        for(int j = 0; j < VisualGrid.y; j++)
        {   
            if(VisualGrid.black_box[i][j])
                result[i][j] = '#';
        }
    }

    // a grapic crossword solution will on be shown if there is one
    // places horizontal words on result table 
    for(int i = 0; i < DataGrid.horizontally->words_count; i++)
    {
        row = DataGrid.horizontally->gap[i].start_row;
        temp = DataGrid.horizontally->gap[i].start_col;
        
        for(int j = 0; j < DataGrid.horizontally->gap[i].length; j++)
        {
            if(DataGrid.horizontally->gap[i].filled == true) 
                result[row][temp+j] = DataGrid.horizontally->gap[i].word[j];  
        }
    }
    // places vertical words on result table 
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
    if (SOLUTION)
    {
        // for the creation of the char table
        char** result = VisualizeResult(DataGrid, VisualGrid);

        for(int i = 0; i < VisualGrid.x; i++)
        {
            for(int j = 0; j < VisualGrid.y; j++)
            {
                if(result[i][j] == '#')     
                    printf("###");
                else    
                    printf(" %c ", result[i][j]);       
            }
            printf("\n");    
        }
        printf("\n");

        FreeResultTable(result, VisualGrid.x);
    }
    else
        printf("CROSSWORD CANNOT BE SOLVED!\n");        
}

void FreeResultTable(char** ResultTable, int Width)
{
    for (int i = 0; i < Width; i++)
        free(ResultTable[i]);
    free(ResultTable);
}