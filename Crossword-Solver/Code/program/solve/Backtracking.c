#include "../../include/solve/Backtracking.h"

void Backtracking(DataGrid* DataGrid, Coordinates Gap, Flag* Flags, int *FLAG)
{
    // we need to find a problematic gap and remove its value
    Coordinates faulty = GetFaultyGap(*DataGrid, Flags, *FLAG);            

    // then faulty is vertical
    if (Flags[faulty.flag].horizontal_gap)                                                      
        RemoveWord(DataGrid, &(DataGrid->horizontally->gap[Flags[faulty.flag].index]), FLAG);
    else                                                                                        
        RemoveWord(DataGrid, &(DataGrid->vertically->gap[Flags[faulty.flag].index]), FLAG);

    // flag is changed to the faulty flag, so that it can be refilled
    *FLAG = faulty.flag;    
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
    // remove vertically
    if(IsHorizontalGap(Gap))                            
        RemoveConstraintsVertically(DataGrid, Gap);
    else                                                
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
    // gap is empty now
    Gap->filled = false;        
    
    for(int i = 0; i < Gap->length; i++)
        Gap->word[i] = ' ';

    RemoveConstraints(DataGrid, *Gap);   

    // flag is set so that the problematic gap can be refilled
    if (*FLAG > 0)      
        (*FLAG)--; 
}