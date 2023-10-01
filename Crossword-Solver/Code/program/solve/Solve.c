#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "../../include/solve/Solve.h"

bool SOLUTION;
int GAP_ORDER = 1;

void Solve(DataGrid* DataGrid, HashTable Dictionary)
{
    Flag* flags;
    SOLUTION = true;

    Initialize(DataGrid, Dictionary);
    flags = FlagInitialize(DataGrid);
    SetIntersections(DataGrid);

    FillCrossword(DataGrid, Dictionary, flags);
}

Flag* FlagInitialize(DataGrid* DataGrid)
{
    int num = DataGrid->horizontally->words_count + DataGrid->vertically->words_count;
    Flag* flags = malloc(num * sizeof(Flag));

    for (int i = 0; i < num; i++)
    {
        flags[i].horizontal_gap = false;
        flags[i].index = -1;
    }
    return flags;
}

void Initialize(DataGrid* DataGrid, HashTable Dictionary)
{
    int length;

    // Initialize horizontal crossword solutions as empty spaces 
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
        
        // basic memory allocation for constraints
        DataGrid->horizontally->gap[i].constraints = malloc((length+1) * sizeof(char));
        DataGrid->horizontally->gap[i].index = -1; 

        for (int k = 0; k < length; k++)
        {
            DataGrid->horizontally->gap[i].word[k] = ' ';
            DataGrid->horizontally->gap[i].constraints[k] = ' ';
        }
    }

    // Initialize vertical crossword solutions as empty spaces
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

        // basic memory allocation for constraints 
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

    while (FLAG != max_flag+1)
    {
        if (GAP_ORDER == 1)
        {
            elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;

            if (elapsed_time >= 3.0 && (DataGrid->horizontally->dimensions <= 25 && DataGrid->vertically->dimensions <= 25))
            {
                GAP_ORDER = 2;
                Solve(DataGrid, Dictionary);
                return;
            }
        }

        if (SOLUTION)
        {
            FillNext(DataGrid, Dictionary, Flags, &FLAG);
            continue;
        }
        return;
    }
}

void FillNext(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int* FLAG)
{
    int index;

    if (!IsGapPrioritySet(Flags, *FLAG))
        SetGapsFillingOrder(DataGrid, Dictionary, Flags, *FLAG, GAP_ORDER);

    if (Flags[*FLAG].horizontal_gap)
    {
        index = Flags[*FLAG].index;
        FillGap(DataGrid, &(DataGrid->horizontally->gap[index]), Dictionary, Flags, FLAG);
    }
    else
    {
        index = Flags[*FLAG].index;
        FillGap(DataGrid, &(DataGrid->vertically->gap[index]), Dictionary, Flags, FLAG);
    }
}

void FillGap(DataGrid* DataGrid, Coordinates* Gap, HashTable Dictionary, Flag* Flags, int* FLAG)
{
    String word;
    word = FindSuitableWord(Gap, Dictionary);

    if (!word)
    {
        if (*FLAG == 0)
            SOLUTION = false;
        else
            Backtracking(DataGrid, *Gap, Flags, FLAG);
        return;
    }

    PlaceWord(DataGrid, Gap, word, FLAG); 

    if (!IsWordAcceptable(*DataGrid, *Gap, Dictionary))
        RemoveWord(DataGrid, Gap, FLAG);
}