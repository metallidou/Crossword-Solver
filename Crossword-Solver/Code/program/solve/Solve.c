#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "../../include/solve/Solve.h"

// at first we assume that the crossword can be solved
bool SOLUTION = true;           
// this declares the approach we decide the order of filling the gaps (there are 2 ways)
int GAP_ORDER = 1;              

void Solve(DataGrid* DataGrid, HashTable HashTable)
{
    // flags refers to the filling priority of the gaps
    Flag* flags;    

    // initialize data grid, for the solution
    Initialize(DataGrid, HashTable);               
    // initialize flag values
    flags = FlagInitialize(DataGrid);               
    // detect intersected gaps
    SetIntersections(DataGrid);                     

    // attempt to solve
    FillCrossword(DataGrid, HashTable, flags);     
}

Flag* FlagInitialize(DataGrid* DataGrid)
{
    // number of flags = number of words to be found
    int num = DataGrid->horizontally->words_count + DataGrid->vertically->words_count;
    Flag* flags = malloc(num * sizeof(Flag));

    // initialize
    for (int i = 0; i < num; i++)           
    {
        flags[i].horizontal_gap = false;    
        flags[i].index = -1;
    }
    return flags;
}

void Initialize(DataGrid* DataGrid, HashTable HashTable)
{
    int length;

    // initialize horizontal crossword gaps
    for(int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        length = DataGrid->horizontally->gap[i].length;
        
        for (int k = 0; k < DataGrid->horizontally->words_count; k++)
        {
            DataGrid->horizontally->gap[k].intersections = malloc(sizeof(Intersections));
            DataGrid->horizontally->gap[k].intersections->gap_index = malloc(DataGrid->vertically->words_count * sizeof(int));
            DataGrid->horizontally->gap[k].intersections->num = 0;
        } 

        // at first all gaps are empty and no words are placed
        DataGrid->horizontally->gap[i].word = malloc((length+1) * sizeof(char));
        DataGrid->horizontally->gap[i].filled = false;
        
        // memory allocation for constraints
        DataGrid->horizontally->gap[i].constraints = malloc((length+1) * sizeof(char));
        DataGrid->horizontally->gap[i].index = -1; 

        for (int k = 0; k < length; k++)
        {
            DataGrid->horizontally->gap[i].word[k] = ' ';           
            DataGrid->horizontally->gap[i].constraints[k] = ' ';
        }
    }

    // initialize vertical crossword gaps
    for(int i = 0; i < DataGrid->vertically->words_count; i++)
    {
        length = DataGrid->vertically->gap[i].length;

        for (int k = 0; k < DataGrid->vertically->words_count; k++)
        {
            DataGrid->vertically->gap[k].intersections = malloc(sizeof(Intersections));
            DataGrid->vertically->gap[k].intersections->gap_index = malloc(DataGrid->horizontally->words_count * sizeof(int));
            DataGrid->vertically->gap[k].intersections->num = 0;   
        }    

        // at first all gaps are empty and no words are placed
        DataGrid->vertically->gap[i].word = malloc((length+1) * sizeof(char));
        DataGrid->vertically->gap[i].filled = false;

        // memory allocation for constraints 
        DataGrid->vertically->gap[i].constraints = malloc((length+1) * sizeof(char));
        DataGrid->vertically->gap[i].index = -1;

        for (int k = 0; k < length; k++)
        {
            DataGrid->vertically->gap[i].word[k] = ' ';
            DataGrid->vertically->gap[i].constraints[k] = ' ';
        }
    }
}

void FillCrossword(DataGrid* DataGrid, HashTable HashTable, Flag* Flags)
{
    clock_t start_time, end_time;
    double elapsed_time;
    int max_flag, FLAG = 0;

    max_flag = DataGrid->horizontally->words_count + DataGrid->vertically->words_count - 1;
    start_time = clock();

    // crossword isn't solved until the gap with the lowest priority is filled
    while (FLAG != max_flag+1)          
    {
        // 1st option for gap filling decision works quite well, but for some cases there is a better option
        if (GAP_ORDER == 1)               
        {
            // we calculate running time of attempting to solve the crossword
            elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;     

            // if we have a relatively small grid and running time exceeds 3 sec, we apply 2nd approach
            if (elapsed_time >= 3.0 && (DataGrid->horizontally->dimensions <= 25 && DataGrid->vertically->dimensions <= 25))
            {
                // apply 2nd approach
                GAP_ORDER = 2;                      
                // solve from the start
                Solve(DataGrid, HashTable);        
                return;
            }
        }

        // if SOLUTION not false, there are still chances of having a result
        if (SOLUTION)                               
        {   
            FillNext(DataGrid, HashTable, Flags, &FLAG);       
            continue;
        }
        return;
    }
    free(Flags);
}

void FillNext(DataGrid* DataGrid, HashTable HashTable, Flag* Flags, int* FLAG)
{
    int index;

    // if gap priority not set, set it
    if (!IsGapPrioritySet(Flags, *FLAG))
        SetGapsFillingOrder(DataGrid, HashTable, Flags, *FLAG, GAP_ORDER);

    // gap in priority is horizontal  
    if (Flags[*FLAG].horizontal_gap)     
    {
        // get gap index
        index = Flags[*FLAG].index;     
        FillGap(DataGrid, &(DataGrid->horizontally->gap[index]), HashTable, Flags, FLAG);
    }
    else    
    {
        index = Flags[*FLAG].index;     
        FillGap(DataGrid, &(DataGrid->vertically->gap[index]), HashTable, Flags, FLAG);
    }
}

void FillGap(DataGrid* DataGrid, Coordinates* Gap, HashTable HashTable, Flag* Flags, int* FLAG)
{
    String word;
    // to fill the gap we search for a word with specific constraints
    word = FindSuitableWord(Gap, HashTable);       

    // word not found
    if (!word)      
    {
        // a solution cannot be found for the first gap to be filled
        // this means that the crossword cannot be solved
        if (*FLAG == 0)                                 
            SOLUTION = false;                          
        else                                            
            Backtracking(DataGrid, *Gap, Flags, FLAG);  
        return;
    }

    // place word in gap
    PlaceWord(DataGrid, Gap, word, FLAG);               

    // we check whether that word creates problematic constraints for a future placement
    // if so we remove it and try something else
    if (!IsWordAcceptable(*DataGrid, *Gap, HashTable)) 
        RemoveWord(DataGrid, Gap, FLAG);
}