#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "../../include/solve/Solve.h"

int FLAG;

void Solve(DataGrid* DataGrid, HashTable Dictionary)
{
    Flag* flags = malloc((DataGrid->horizontally->words_count + DataGrid->vertically->words_count) * sizeof(Flag));;
    FLAG = 0;

    Initialize(DataGrid, flags, Dictionary);

    IntersectionsHorizontally(DataGrid);
    IntersectionsVertically(DataGrid);

    SolveCrossword(DataGrid, Dictionary, flags);
}

void Initialize(DataGrid* DataGrid, Flag* Flags, HashTable Dictionary)
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

    for (int i = 0; i < (DataGrid->horizontally->words_count + DataGrid->vertically->words_count); i++)
    {
        Flags[i].horizontal_gap = false;
        Flags[i].index = -1;
    }
}

void IntersectionsHorizontally(DataGrid* DataGrid)
{
    int num, row1_index, row2_index, col_index, temp, start, end;

    for (int i = 0; i < DataGrid->vertically->words_count; i++)
    {
        row1_index = DataGrid->vertically->gap[i].start_row;
        row2_index = DataGrid->vertically->gap[i].end_row;
        col_index = DataGrid->vertically->gap[i].start_col;

        for (int j = 0; j < DataGrid->horizontally->words_count; j++)
        {
            start = DataGrid->horizontally->gap[j].start_col;
            end = DataGrid->horizontally->gap[j].end_col;
            temp = DataGrid->horizontally->gap[j].start_row;

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

    for (int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        row_index = DataGrid->horizontally->gap[i].start_row;
        col1_index = DataGrid->horizontally->gap[i].start_col;
        col2_index = DataGrid->horizontally->gap[i].end_col;

        for (int j = 0; j < DataGrid->vertically->words_count; j++)
        {
            start = DataGrid->vertically->gap[j].start_row;
            end = DataGrid->vertically->gap[j].end_row;
            temp = DataGrid->vertically->gap[j].start_col;
        
            if ((start <= row_index && end >= row_index) && (temp >= col1_index && temp <= col2_index))
            {
                num = DataGrid->horizontally->gap[i].intersections->num;
                DataGrid->horizontally->gap[i].intersections->gap_index[num] = j;
                DataGrid->horizontally->gap[i].intersections->num++;
            }
        }
    }
}

void SolveCrossword(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags)
{
    int max_flag = DataGrid->horizontally->words_count + DataGrid->vertically->words_count - 1;
    
    //while (FLAG != max_flag+1)
    for(int i = 0; i < 20000000; i++)
    {
        if(FLAG == max_flag+1)
            break;
        if (Flags[FLAG].index == -1)
            SetGapsFillingOrder(DataGrid, Dictionary, Flags, FLAG);

        GetGapToFill(DataGrid, Dictionary, Flags, FLAG);
    }
}

void SetGapsFillingOrder(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag)
{
    if (CurrentFlag == 0)
    {
        int length, max1, max2;
        max1 = max2 = INT_MIN;
    
        for (int i = 0; i < DataGrid->horizontally->words_count; i++)
        {
            length = DataGrid->horizontally->gap[i].length;
            if (length > max1)
            {
                max1 = length;
                Flags[CurrentFlag].horizontal_gap = true;
                Flags[CurrentFlag].index = i;
            }
        }
        for (int i = 0; i < DataGrid->vertically->words_count; i++)
        {
            length = DataGrid->vertically->gap[i].length;
            if (length > max1)
            {
                max1 = length;  
                Flags[CurrentFlag].horizontal_gap = false;
                Flags[CurrentFlag].index = i;
            }
        }
    }
    else
    {
        int num, min_num = INT_MAX;

        for (int i = 0; i < DataGrid->horizontally->words_count; i++)
        {
            if (DataGrid->horizontally->gap[i].filled == true)
                continue;
            num = GetWordsNumber(DataGrid->horizontally->gap[i], Dictionary);

            if (num < min_num)
            {
                min_num = num;
                Flags[CurrentFlag].horizontal_gap = true;
                Flags[CurrentFlag].index = i;
            }
        }
        for (int i = 0; i < DataGrid->vertically->words_count; i++)
        {
            if (DataGrid->vertically->gap[i].filled == true)
                continue;
            num = GetWordsNumber(DataGrid->vertically->gap[i], Dictionary);

            if (num < min_num)
            {
                min_num = num;
                Flags[CurrentFlag].horizontal_gap = false;
                Flags[CurrentFlag].index = i;
            }
        }
    }

    if (Flags[CurrentFlag].horizontal_gap == true)
        DataGrid->horizontally->gap[Flags[CurrentFlag].index].flag = CurrentFlag;
    else
        DataGrid->vertically->gap[Flags[CurrentFlag].index].flag = CurrentFlag;
}

void GetGapToFill(DataGrid* DataGrid, HashTable Dictionary, Flag* Flags, int CurrentFlag)
{
    int index = Flags[CurrentFlag].index;

    if (Flags[CurrentFlag].horizontal_gap)
    {
        if (DataGrid->horizontally->gap[index].filled == false)
            ChooseWordToFillGap(DataGrid, &(DataGrid->horizontally->gap[index]), Dictionary, Flags, CurrentFlag);
    }
    else 
    {
        if (DataGrid->vertically->gap[index].filled == false)
            ChooseWordToFillGap(DataGrid, &(DataGrid->vertically->gap[index]), Dictionary, Flags, CurrentFlag);
    }
}

void ChooseWordToFillGap(DataGrid* DataGrid, Coordinates* Gap, HashTable Dictionary, Flag* Flags, int CurrentFlag)
{
    char* word = GetWord(Gap, Dictionary);

    if (word == NULL)
    {
        Backtracking(DataGrid, *Gap, Flags, CurrentFlag);
        return;
    }
        
    PlaceWord(DataGrid, Gap, word);
        
    if (!IsValid(*DataGrid, *Gap, Dictionary))
    {
        RemoveWord(DataGrid, Gap);
        if (FLAG > 0)
            FLAG--;
    }
}

bool IsValid(DataGrid DataGrid, Coordinates Gap, HashTable Dictionary)
{
    int index, temp;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        index = Gap.intersections->gap_index[i];

        if (IsHorizontalGap(Gap))
        {
            temp = DataGrid.vertically->gap[index].index;

            if (!DataGrid.vertically->gap[index].filled)
            {
                if (GetWord(&(DataGrid.vertically->gap[index]), Dictionary) == NULL)
                {
                    DataGrid.vertically->gap[index].index = temp;
                    return false;
                }
                DataGrid.vertically->gap[index].index = temp;
            }
        }
        else
        {
            temp = DataGrid.horizontally->gap[index].index;

            if (!DataGrid.horizontally->gap[index].filled)
            {
                if (GetWord(&(DataGrid.horizontally->gap[index]), Dictionary) == NULL)
                {
                    DataGrid.horizontally->gap[index].index = temp;
                    return false;
                }   
                DataGrid.horizontally->gap[index].index = temp;
            }
        }   
    }
    return true;
}

Vector SetWordsVector(Coordinates Gap, HashTable Dictionary)
{
    int index, possibiities = INT_MAX;
    bool has_constraints = false;
    char letter, ch;

    for (int i = 0; i < Gap.length; i++)
    {
        ch = Gap.constraints[i];
        
        if (ch == ' ')  
            continue;
        
        if (Dictionary.length[Gap.length].position[i].letter[(int)(ch)-97].words.size < possibiities)
        {
            possibiities = Dictionary.length[Gap.length].position[i].letter[(int)(ch)-97].words.size;
            index = i;
            letter = ch;
            has_constraints = true;
        }
    }

    if (has_constraints == false)
        return Dictionary.length[Gap.length].words;
    return Dictionary.length[Gap.length].position[index].letter[(int)(letter)-97].words;
}

int GetWordsNumber(Coordinates Gap, HashTable Dictionary)
{
    Vector words_vector = SetWordsVector(Gap, Dictionary);
    int count = 0;
    bool suitable;

    for (int i = 0; i < words_vector.size; i++)
    {
        suitable = true;

        for (int j = 0; j < Gap.length; j++)
        {
            if (Gap.constraints[j] == ' ')
                continue;
            if (Gap.constraints[j] != words_vector.word[i][j])
                suitable = false;
        }
        if (suitable == true)   
            count++;
    }
    return count;
}

String GetWord(Coordinates* Gap, HashTable Dictionary)
{
    Vector* words_vector = malloc(sizeof(Vector));
    bool suitable;

    if (Gap->index == -1)
    {
        *words_vector = SetWordsVector(*Gap, Dictionary);
        Gap->words_vector = words_vector;
    }
    else
        words_vector = Gap->words_vector;

    for (int i = Gap->index+1; i < words_vector->size; i++)
    {
        suitable = true;

        for (int j = 0; j < Gap->length; j++)
        {
            if (Gap->constraints[j] == ' ')
                continue;
            if (Gap->constraints[j] != words_vector->word[i][j])
                suitable = false;
        }
        
        if (suitable == true)
        {
            Gap->index = i;
            return words_vector->word[i];
        }
    }
    Gap->index = -1;
    return NULL;
}

void PlaceWord(DataGrid* DataGrid, Coordinates* Gap, String Word)
{
    Gap->filled = true;
    strcpy(Gap->word, Word);

    AddConstraints(DataGrid, *Gap);
    FLAG++;
}

void Backtracking(DataGrid* DataGrid, Coordinates Gap, Flag* Flags, int CurrentFlag)
{
    Coordinates faulty;

    faulty = GetFaultyGap(*DataGrid, Flags, CurrentFlag);

    if (Flags[faulty.flag].horizontal_gap)
        RemoveWord(DataGrid, &(DataGrid->horizontally->gap[Flags[faulty.flag].index]));
    else
        RemoveWord(DataGrid, &(DataGrid->vertically->gap[Flags[faulty.flag].index]));

    FLAG = faulty.flag;
}

Coordinates GetFaultyGap(DataGrid DataGrid, Flag* Flags, int CurrentFlag)
{
    if (Flags[CurrentFlag-1].horizontal_gap == true)
        return DataGrid.horizontally->gap[Flags[CurrentFlag-1].index];   
    return DataGrid.vertically->gap[Flags[CurrentFlag-1].index];
}

void AddConstraints(DataGrid* DataGrid, Coordinates Gap)
{
    if(IsHorizontalGap(Gap))
        AddConstraintsVertically(DataGrid, Gap);
    else
        AddConstraintsHorizontally(DataGrid, Gap);     
}

void RemoveConstraints(DataGrid* DataGrid, Coordinates Gap)
{
    if(IsHorizontalGap(Gap))
        RemoveConstraintsVertically(DataGrid, Gap);
    else
        RemoveConstraintsHorizontally(DataGrid, Gap);  
}

void AddConstraintsHorizontally(DataGrid* DataGrid, Coordinates Gap)
{
    int gap_index, row_index, col_index, temp, start;
    
    row_index = Gap.start_row;
    col_index = Gap.start_col;

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

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        gap_index = Gap.intersections->gap_index[i];
        start = DataGrid->vertically->gap[gap_index].start_row;
        temp = DataGrid->vertically->gap[gap_index].start_col;
        DataGrid->vertically->gap[gap_index].constraints[row_index-start] = Gap.word[temp-col_index];  
    }
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

void RemoveWord(DataGrid* DataGrid, Coordinates* Gap)
{
    Gap->filled = false;
    
    for(int i = 0; i < Gap->length; i++)
        Gap->word[i] = ' ';

    RemoveConstraints(DataGrid, *Gap);    
}

int IsHorizontalGap(Coordinates Gap)
{
    return (Gap.start_row == Gap.end_row);
}