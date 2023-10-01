#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "../../include/solve/Solve.h"

bool SOLUTION = true;           // at first we assume that the crossword can be solved
int GAP_ORDER = 1;              // this declares the approach we decide the order of filling the gaps (there are 2 ways)

void Solve(DataGrid* DataGrid, HashTable Dictionary)
{
    Flag* flags;    // flags refers to the filling priority of the gaps

    Initialize(DataGrid, Dictionary);               // initialize data grid, for the solution
    flags = FlagInitialize(DataGrid);               // initialize flag values
    SetIntersections(DataGrid);                     // detect intersected gaps

    FillCrossword(DataGrid, Dictionary, flags);     // attempt to solve
}

Flag* FlagInitialize(DataGrid* DataGrid)
{
    // number of flags = number of words to be found
    int num = DataGrid->horizontally->words_count + DataGrid->vertically->words_count;
    Flag* flags = malloc(num * sizeof(Flag));

    for (int i = 0; i < num; i++)           // initialize
    {
        flags[i].horizontal_gap = false;    
        flags[i].index = -1;
    }
    return flags;
}

void Initialize(DataGrid* DataGrid, HashTable Dictionary)
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

void FillCrossword(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags)
{
    clock_t start_time, end_time;
    double elapsed_time;
    int max_flag, FLAG = 0;

    max_flag = DataGrid->horizontally->words_count + DataGrid->vertically->words_count - 1;
    start_time = clock();

    while (FLAG != max_flag+1)          // crossword isn't solved until the gap with the lowest priority is filled
    {
        if (GAP_ORDER == 1)             // 1st option for gap filling decision works quite well, but for some cases there is a better option  
        {
            // we calculate running time of attempting to solve the crossword
            elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;     

            // if we have a relatively small grid and running time exceeds 3 sec, we apply 2nd approach
            if (elapsed_time >= 3.0 && (DataGrid->horizontally->dimensions <= 25 && DataGrid->vertically->dimensions <= 25))
            {
                GAP_ORDER = 2;                      // apply 2nd approach
                Solve(DataGrid, Dictionary);        // solve from the start
                return;
            }
        }

        // if SOLUTION not false, there are still chances of having a result
        if (SOLUTION)                               
        {   
            FillNext(DataGrid, Dictionary, Flags, &FLAG);       // fill next gap
            continue;
        }
        return;
    }
}

void FillNext(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int* FLAG)
{
    int index;

    // if gap priority not set, set it
    if (!IsGapPrioritySet(Flags, *FLAG))
        SetGapsFillingOrder(DataGrid, Dictionary, Flags, *FLAG, GAP_ORDER);

    if (Flags[*FLAG].horizontal_gap)    // gap in priority is horizontal   
    {
        index = Flags[*FLAG].index;     // get gap index
        FillGap(DataGrid, &(DataGrid->horizontally->gap[index]), Dictionary, Flags, FLAG);
    }
    else    // gap in priority is vertical
    {
        index = Flags[*FLAG].index;     // get gap index
        FillGap(DataGrid, &(DataGrid->vertically->gap[index]), Dictionary, Flags, FLAG);
    }
}

void FillGap(DataGrid* DataGrid, Coordinates* Gap, HashTable Dictionary, Flag* Flags, int* FLAG)
{
    String word;
    word = FindSuitableWord(Gap, Dictionary);       // to fill the gap we search for a word with specific constraints

    if (!word)      // word not found
    {
        if (*FLAG == 0)                                 // a solution cannot be found for the first gap to be filled
            SOLUTION = false;                           // this means that the crossword cannot be solved
        else                                            // we can do a backtrack, so that we can erase a potential problematic word and replace it with another one 
            Backtracking(DataGrid, *Gap, Flags, FLAG);  
        return;
    }

    PlaceWord(DataGrid, Gap, word, FLAG);               // place word in gap

    // we check whether that word creates problematic constraints for a future placement
    // if so we remove it and try something else
    if (!IsWordAcceptable(*DataGrid, *Gap, Dictionary)) 
        RemoveWord(DataGrid, Gap, FLAG);
}