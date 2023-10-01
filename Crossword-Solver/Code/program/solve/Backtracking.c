#include "../../include/solve/Backtracking.h"

void Backtracking(DataGrid* DataGrid, Coordinates Gap, Flag* Flags, int *FLAG)
{
    // we need to find a problematic gap and remove its value
    Coordinates faulty = GetFaultyGap(*DataGrid, Flags, *FLAG);            

    if (Flags[faulty.flag].horizontal_gap)                                                      // then faulty is vertical
        RemoveWord(DataGrid, &(DataGrid->horizontally->gap[Flags[faulty.flag].index]), FLAG);
    else                                                                                        // then faulty is horizontal
        RemoveWord(DataGrid, &(DataGrid->vertically->gap[Flags[faulty.flag].index]), FLAG);

    *FLAG = faulty.flag;    // flag is changed to the faulty flag, so that i can be refilled
}

Coordinates GetFaultyGap(DataGrid DataGrid, Flag* Flags, int CurrentFlag)
{
    // the faulty gap is the previously filled one
    if (Flags[CurrentFlag-1].horizontal_gap)    
        return DataGrid.horizontally->gap[Flags[CurrentFlag-1].index];   
    return DataGrid.vertically->gap[Flags[CurrentFlag-1].index];
}

void RemoveConstraints(DataGrid* DataGrid, Coordinates Gap)
{
    if(IsHorizontalGap(Gap))                            // remove vertically
        RemoveConstraintsVertically(DataGrid, Gap);
    else                                                // remove horizontally
        RemoveConstraintsHorizontally(DataGrid, Gap);  
}

void RemoveConstraintsHorizontally(DataGrid* DataGrid, Coordinates Gap)
{
    int gap_index, col_index, start;
    col_index = Gap.start_col;

    for (int i = 0; i < Gap.intersections->num; i++)    
    {
        gap_index = Gap.intersections->gap_index[i];
        start = DataGrid->horizontally->gap[gap_index].start_col; 
        DataGrid->horizontally->gap[gap_index].constraints[col_index-start] = ' ';  
    }
}

void RemoveConstraintsVertically(DataGrid* DataGrid, Coordinates Gap)
{
    int gap_index, row_index, temp, start;
    row_index = Gap.start_row;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        gap_index = Gap.intersections->gap_index[i];
        start = DataGrid->vertically->gap[gap_index].start_row;
        DataGrid->vertically->gap[gap_index].constraints[row_index-start] = ' ';  
    }
}

void RemoveWord(DataGrid* DataGrid, Coordinates* Gap, int* FLAG)
{
    Gap->filled = false;        // gap is empty now
    
    for(int i = 0; i < Gap->length; i++)
        Gap->word[i] = ' ';

    RemoveConstraints(DataGrid, *Gap);   

    if (*FLAG > 0)      // flag is set so that the problematic gap can be refilled
        (*FLAG)--; 
}