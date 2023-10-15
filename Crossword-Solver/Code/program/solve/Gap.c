#include <limits.h>
#include "../../include/solve/Gap.h"

bool IsGapPrioritySet(Flag* Flags, int CurrentFlag)
{   
    // then priority not set yet
    if (Flags[CurrentFlag].index == -1)         
        return false;
    return true;
}

void SetIntersections(DataGrid* DataGrid)
{
    IntersectionsHorizontally(DataGrid);     
    IntersectionsVertically(DataGrid);
}

void IntersectionsHorizontally(DataGrid* DataGrid)
{
    int num, row1_index, row2_index, col_index, temp, start, end;

    // for each gap horizontally
    for (int i = 0; i < DataGrid->vertically->words_count; i++)             
    {
        // coordinates that refer to the gap position
        row1_index = DataGrid->vertically->gap[i].start_row;                
        row2_index = DataGrid->vertically->gap[i].end_row;
        col_index = DataGrid->vertically->gap[i].start_col;

        // for each gap vertically
        for (int j = 0; j < DataGrid->horizontally->words_count; j++)       
        {
            start = DataGrid->horizontally->gap[j].start_col;
            end = DataGrid->horizontally->gap[j].end_col;
            temp = DataGrid->horizontally->gap[j].start_row;

            // if the horizontal gap and the vertical gap are intersected
            if ((start <= col_index && end >= col_index) && (temp >= row1_index && temp <= row2_index))  
            {
                num = DataGrid->vertically->gap[i].intersections->num;
                DataGrid->vertically->gap[i].intersections->gap_index[num] = j;     
                DataGrid->vertically->gap[i].intersections->num++;      
            }
        }    
    }
}

void IntersectionsVertically(DataGrid* DataGrid)
{
    int num, row_index, col1_index, col2_index, temp, start, end;

    // for each gap vertically
    for (int i = 0; i < DataGrid->horizontally->words_count; i++)           
    {
        // coordinates that refer to the gap position
        row_index = DataGrid->horizontally->gap[i].start_row;               
        col1_index = DataGrid->horizontally->gap[i].start_col;
        col2_index = DataGrid->horizontally->gap[i].end_col;

        // for each gap horizontaly
        for (int j = 0; j < DataGrid->vertically->words_count; j++)         
        {
            start = DataGrid->vertically->gap[j].start_row;
            end = DataGrid->vertically->gap[j].end_row;
            temp = DataGrid->vertically->gap[j].start_col;
        
            // if the horizontal gap and the vertical gap are intersected
            if ((start <= row_index && end >= row_index) && (temp >= col1_index && temp <= col2_index))
            {
                num = DataGrid->horizontally->gap[i].intersections->num;
                DataGrid->horizontally->gap[i].intersections->gap_index[num] = j;   
                DataGrid->horizontally->gap[i].intersections->num++;
            }
        }
    }
}

void SetGapsFillingOrder(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag, int GapOrder)
{
    if (CurrentFlag == 0)    
    {
        SetFirstGapToFill(DataGrid, Flags);
        return;
    }

    switch (GapOrder)
    {
        // approach 1
        case 1:
            SetGapsFillingOrder_1(DataGrid, Dictionary, Flags, CurrentFlag);        
            return;
        // approach 2
        case 2:
            SetGapsFillingOrder_2(DataGrid, Dictionary, Flags, CurrentFlag);        
            return;
    }        
}

void SetFirstGapToFill(DataGrid* DataGrid, Flag* Flags)
{
    int intersections, max1, max2;
    max1 = max2 = INT_MIN;          
    
    for (int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        // the gap with the most intersected gaps has highest priority
        intersections = DataGrid->horizontally->gap[i].intersections->num;  
        if (intersections > max1)   
        {
            max1 = intersections;
            Flags[0].horizontal_gap = true;
            Flags[0].index = i;
            }
    }
    for (int i = 0; i < DataGrid->vertically->words_count; i++)     
    {
        intersections = DataGrid->vertically->gap[i].intersections->num;
        if (intersections > max1)
        {
                max1 = intersections;  
                Flags[0].horizontal_gap = false;
                Flags[0].index = i;
        }
    }
    // set the gap with the highest priority
    if (Flags[0].horizontal_gap)
        DataGrid->horizontally->gap[Flags[0].index].flag = 0;
    else
        DataGrid->vertically->gap[Flags[0].index].flag = 0;
}

void SetGapsFillingOrder_1(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag)
{   
    int num, min_num = INT_MAX;     

    for (int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        // ignore an already filled gap
        if (DataGrid->horizontally->gap[i].filled)      
            continue;
        // the number of words with constraints that can fit in the gap declares its priority    
        num = GetNumberOfSuitableWords(DataGrid->horizontally->gap[i], Dictionary); 

        if (num < min_num)      
        {
            min_num = num;
            Flags[CurrentFlag].horizontal_gap = true;
            Flags[CurrentFlag].index = i;
        }
    }
    for (int i = 0; i < DataGrid->vertically->words_count; i++)     
    {
        if (DataGrid->vertically->gap[i].filled)
            continue;
        num = GetNumberOfSuitableWords(DataGrid->vertically->gap[i], Dictionary);

        if (num < min_num)
        {
            min_num = num;
            Flags[CurrentFlag].horizontal_gap = false;
            Flags[CurrentFlag].index = i;
        }
    }

    // set the gap with the highest priority
    if (Flags[CurrentFlag].horizontal_gap)
        DataGrid->horizontally->gap[Flags[CurrentFlag].index].flag = CurrentFlag;
    else
        DataGrid->vertically->gap[Flags[CurrentFlag].index].flag = CurrentFlag;
}

void SetGapsFillingOrder_2(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag)
{
    int index, num, max_num = INT_MIN;

    for (int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        // gap already filled
        if (DataGrid->horizontally->gap[i].filled == true)      
            continue;
        num = 0;

        // we get the number of the intersected words
        for (int j = 0; j < DataGrid->horizontally->gap[i].intersections->num; j++)
        {
            index = DataGrid->horizontally->gap[i].intersections->gap_index[j];
            if (DataGrid->vertically->gap[index].filled)
                num++;
        }
        if (num > max_num)      
        {
            max_num = num;
            Flags[CurrentFlag].horizontal_gap = true;
            Flags[CurrentFlag].index = i;
        }
    }
    for (int i = 0; i < DataGrid->vertically->words_count; i++)         
    {
        if (DataGrid->vertically->gap[i].filled == true)
            continue;
        num = 0;

        for (int j = 0; j < DataGrid->vertically->gap[i].intersections->num; j++)
        {
            index = DataGrid->vertically->gap[i].intersections->gap_index[j];
            if (DataGrid->horizontally->gap[index].filled)
                num++;
        }    
        if (num > max_num)
        {
            max_num = num;
            Flags[CurrentFlag].horizontal_gap = false;
            Flags[CurrentFlag].index = i;
        }
    }

    // set highest priority gap
    if (Flags[CurrentFlag].horizontal_gap)
        DataGrid->horizontally->gap[Flags[CurrentFlag].index].flag = CurrentFlag;
    else
        DataGrid->vertically->gap[Flags[CurrentFlag].index].flag = CurrentFlag;
}

Coordinates GetGap(DataGrid DataGrid, Flag* Flags, int CurrentFlag)
{
    // returns the gap that corresponds to the above
    if (Flags[CurrentFlag].horizontal_gap)
        return DataGrid.horizontally->gap[Flags[CurrentFlag].index];
    return DataGrid.vertically->gap[Flags[CurrentFlag].index];
}

void AddConstraints(DataGrid* DataGrid, Coordinates Gap)
{   
    // if the gap filled was horizontal, it creates constraints for other vertical gaps
    if(IsHorizontalGap(Gap))                        
        AddConstraintsVertically(DataGrid, Gap);
    else                                            
        AddConstraintsHorizontally(DataGrid, Gap);         
}

void AddConstraintsHorizontally(DataGrid* DataGrid, Coordinates Gap)
{
    int gap_index, row_index, col_index, temp, start;
    
    row_index = Gap.start_row;
    col_index = Gap.start_col;

    // add contraints to the intersected words
    for (int i = 0; i < Gap.intersections->num; i++)        
    {
        gap_index = Gap.intersections->gap_index[i];
        start = DataGrid->horizontally->gap[gap_index].start_col;
        temp = DataGrid->horizontally->gap[gap_index].start_row;
        DataGrid->horizontally->gap[gap_index].constraints[col_index-start] = Gap.word[temp-row_index];
    }
}

void AddConstraintsVertically(DataGrid* DataGrid, Coordinates Gap)
{
    int gap_index, row_index, col_index, temp, start;
    
    row_index = Gap.start_row;
    col_index = Gap.start_col;

    // add contraints to the intersected words
    for (int i = 0; i < Gap.intersections->num; i++)        
    {
        gap_index = Gap.intersections->gap_index[i];
        start = DataGrid->vertically->gap[gap_index].start_row;
        temp = DataGrid->vertically->gap[gap_index].start_col;
        DataGrid->vertically->gap[gap_index].constraints[row_index-start] = Gap.word[temp-col_index];  
    }
}

int IsHorizontalGap(Coordinates Gap)
{
    return (Gap.start_row == Gap.end_row);
}