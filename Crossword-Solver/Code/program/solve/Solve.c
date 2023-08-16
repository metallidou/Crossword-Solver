#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "../../include/solve/Solve.h"

int FLAG;

Grid Solve(Grid DataGrid, HashTable Dictionary)
{
    Flags* flags;
    FLAG = 0;

    Initialize(DataGrid, Dictionary);
    flags = FlagsInitialize(DataGrid, flags);

    DataGrid = IntersectionsHorizontally(DataGrid);
    DataGrid = IntersectionsVertically(DataGrid);

    DataGrid = SolveCrossword(DataGrid, Dictionary, flags);

    return DataGrid;
}

void Initialize(Grid DataGrid, HashTable Dictionary)
{
    int length;

    // Initialize horizontal crossword solutions as empty spaces 
    for(int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        length = DataGrid->horizontally->coordinates[i].length;
        
        for (int k = 0; k < DataGrid->horizontally->words_count; k++)
        {
            DataGrid->horizontally->coordinates[k].intersections = malloc(sizeof(struct GridINTERSECTIONS));
            DataGrid->horizontally->coordinates[k].intersections->gap_index = malloc(DataGrid->vertically->words_count * sizeof(int));
            DataGrid->horizontally->coordinates[k].intersections->num = 0;
        } 

        // at first all gaps are empty and no words are placed
        DataGrid->horizontally->coordinates[i].solution = malloc(sizeof(struct CrosswordSOLUTION));
        DataGrid->horizontally->coordinates[i].solution->word = malloc((length+1) * sizeof(char));
        DataGrid->horizontally->coordinates[i].solution->filled = false;
        DataGrid->horizontally->coordinates[i].solution->backtracking = false;
        
        // basic memory allocation for constraints
        DataGrid->horizontally->coordinates[i].solution->constraints = malloc(sizeof(struct CrosswordCONSTRAINTS));
        DataGrid->horizontally->coordinates[i].solution->constraints->letters = malloc((length+1) * sizeof(char));
        DataGrid->horizontally->coordinates[i].solution->constraints->used_index = -1;

        for(int j = 0; j < length; j++)
        {
            DataGrid->horizontally->coordinates[i].solution->word[j] = ' ';
            DataGrid->horizontally->coordinates[i].solution->constraints->letters[j] = ' ';
        }
    }

    // Initialize vertical crossword solutions as empty spaces
    for(int i = 0; i < DataGrid->vertically->words_count; i++)
    {
        length = DataGrid->vertically->coordinates[i].length;

        for (int k = 0; k < DataGrid->vertically->words_count; k++)
        {
            DataGrid->vertically->coordinates[k].intersections = malloc(sizeof(struct GridINTERSECTIONS));
            DataGrid->vertically->coordinates[k].intersections->gap_index = malloc(DataGrid->horizontally->words_count * sizeof(int));
            DataGrid->vertically->coordinates[k].intersections->num = 0;   
        }    

        // at first all gaps are empty and no words are placed
        DataGrid->vertically->coordinates[i].solution = malloc(sizeof(struct CrosswordSOLUTION));
        DataGrid->vertically->coordinates[i].solution->word = malloc((length+1) * sizeof(char));
        DataGrid->vertically->coordinates[i].solution->backtracking = false;
        DataGrid->vertically->coordinates[i].solution->filled = false;

        // basic memory allocation for constraints 
        DataGrid->vertically->coordinates[i].solution->constraints = malloc(sizeof(struct CrosswordCONSTRAINTS));
        DataGrid->vertically->coordinates[i].solution->constraints->letters = malloc((length+1) * sizeof(char));
        DataGrid->vertically->coordinates[i].solution->constraints->used_index = -1;

        for(int j = 0; j < length; j++)
        {
            DataGrid->vertically->coordinates[i].solution->word[j] = ' ';
            DataGrid->vertically->coordinates[i].solution->constraints->letters[j] = ' ';
        }
    }
}

Flags* FlagsInitialize(Grid DataGrid, Flags* Flags)
{
    Flags = malloc((DataGrid->horizontally->words_count + DataGrid->vertically->words_count) * sizeof(Flags));
    for (int i = 0; i < (DataGrid->horizontally->words_count + DataGrid->vertically->words_count); i++)
    {
        Flags[i] = malloc(sizeof(struct CrosswordFLAGS));
        Flags[i]->horizontal_gap = false;
        Flags[i]->index = -1;
    }
    return Flags;    
}

Grid IntersectionsHorizontally(Grid DataGrid)
{
    int num, row1_index, row2_index, col_index, temp, start, end;

    for (int i = 0; i < DataGrid->vertically->words_count; i++)
    {
        row1_index = DataGrid->vertically->coordinates[i].start_row;
        row2_index = DataGrid->vertically->coordinates[i].end_row;
        col_index = DataGrid->vertically->coordinates[i].start_col;

        for (int j = 0; j < DataGrid->horizontally->words_count; j++)
        {
            start = DataGrid->horizontally->coordinates[j].start_col;
            end = DataGrid->horizontally->coordinates[j].end_col;
            temp = DataGrid->horizontally->coordinates[j].start_row;

            if ((start <= col_index && end >= col_index) && (temp >= row1_index && temp <= row2_index))  
            {
                num = DataGrid->vertically->coordinates[i].intersections->num;
                DataGrid->vertically->coordinates[i].intersections->gap_index[num] = j;
                DataGrid->vertically->coordinates[i].intersections->num++;
            }
        }    
    }
    return DataGrid;
}

Grid IntersectionsVertically(Grid DataGrid)
{
    int num, row_index, col1_index, col2_index, temp, start, end;

    for (int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        row_index = DataGrid->horizontally->coordinates[i].start_row;
        col1_index = DataGrid->horizontally->coordinates[i].start_col;
        col2_index = DataGrid->horizontally->coordinates[i].end_col;

        for (int j = 0; j < DataGrid->vertically->words_count; j++)
        {
            start = DataGrid->vertically->coordinates[j].start_row;
            end = DataGrid->vertically->coordinates[j].end_row;
            temp = DataGrid->vertically->coordinates[j].start_col;
        
            if ((start <= row_index && end >= row_index) && (temp >= col1_index && temp <= col2_index))
            {
                num = DataGrid->horizontally->coordinates[i].intersections->num;
                DataGrid->horizontally->coordinates[i].intersections->gap_index[num] = j;
                DataGrid->horizontally->coordinates[i].intersections->num++;
            }
        }
    }
    return DataGrid;
}

Grid SolveCrossword(Grid DataGrid, HashTable Dictionary, Flags* Flags)
{
    int max_flag = DataGrid->horizontally->words_count + DataGrid->vertically->words_count - 1;
    
    //while (FLAG != max_flag+1)
    for(int i = 0; i < 10000000; i++)
    {
        if(FLAG == max_flag+1)
            break;
        if (Flags[FLAG]->index == -1)
            DataGrid = SetGapsFillingOrder(DataGrid, Dictionary, Flags, FLAG);

        DataGrid = GetGapToFill(DataGrid, Dictionary, Flags, FLAG);
    }
    return DataGrid;
}

Grid SetGapsFillingOrder(Grid DataGrid, HashTable Dictionary, Flags* Flags, int CurrentFlag)
{
    if (CurrentFlag == 0)
    {
        int length, max1, max2;
        max1 = max2 = INT_MIN;

        for (int i = 0; i < DataGrid->horizontally->words_count; i++)
        {
            length = DataGrid->horizontally->coordinates[i].length;
            if (length > max1)
            {
                max1 = length;
                Flags[CurrentFlag]->horizontal_gap = true;
                Flags[CurrentFlag]->index = i;
            }
        }
        for (int i = 0; i < DataGrid->vertically->words_count; i++)
        {
            length = DataGrid->vertically->coordinates[i].length;
            if (length > max2)
            {
                max2 = length;  
                Flags[CurrentFlag]->horizontal_gap = false;
                Flags[CurrentFlag]->index = i;
            }
        }
    }
    else
    {
        int num, min_num = INT_MAX;

        for (int i = 0; i < DataGrid->horizontally->words_count; i++)
        {
            if (DataGrid->horizontally->coordinates[i].solution->filled == true)
                continue;
            num = GetWordsNumber(DataGrid->horizontally->coordinates[i], Dictionary);

            if (num < min_num)
            {
                min_num = num;
                Flags[CurrentFlag]->horizontal_gap = true;
                Flags[CurrentFlag]->index = i;
            }
        }
        for (int i = 0; i < DataGrid->vertically->words_count; i++)
        {
            if (DataGrid->vertically->coordinates[i].solution->filled == true)
                continue;
            num = GetWordsNumber(DataGrid->vertically->coordinates[i], Dictionary);

            if (num < min_num)
            {
                min_num = num;
                Flags[CurrentFlag]->horizontal_gap = false;
                Flags[CurrentFlag]->index = i;
            }
        }
    }

    if (Flags[CurrentFlag]->horizontal_gap == true)
        DataGrid->horizontally->coordinates[Flags[CurrentFlag]->index].flag = CurrentFlag;
    else
        DataGrid->vertically->coordinates[Flags[CurrentFlag]->index].flag = CurrentFlag;
        
    return DataGrid;
}

Grid GetGapToFill(Grid DataGrid, HashTable Dictionary, Flags* Flags, int CurrentFlag)
{
    int index;

    if (Flags[CurrentFlag]->horizontal_gap == true)
    {
        index = Flags[CurrentFlag]->index;
        if (DataGrid->horizontally->coordinates[index].solution->filled == false)
            DataGrid = ChooseWordToFillGap(DataGrid, DataGrid->horizontally->coordinates[index], Dictionary, Flags, CurrentFlag);
    }
    else 
    {
        index = Flags[CurrentFlag]->index;
        if (DataGrid->vertically->coordinates[index].solution->filled == false)
            DataGrid = ChooseWordToFillGap(DataGrid, DataGrid->vertically->coordinates[index], Dictionary, Flags, CurrentFlag);
    }
    return DataGrid;
}

Grid ChooseWordToFillGap(Grid DataGrid, struct GridCOORDINATES Gap, HashTable Dictionary, Flags* Flags, int CurrentFlag)
{
    char* word = GetWord(Gap, Dictionary);

    if (word == NULL)
        DataGrid = Backtracking(DataGrid, Gap, Flags, CurrentFlag);
    else
    {
        DataGrid = PlaceWord(DataGrid, Gap, word);
        
        if (IsValid(DataGrid, Gap, Dictionary) == false)
        {
            RemoveWord(DataGrid, Gap);
            if (FLAG > 0)
                FLAG--;
        }
    }
    return DataGrid;
}

bool IsValid(Grid DataGrid, struct GridCOORDINATES Gap, HashTable Dictionary)
{
    int index, temp;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        index = Gap.intersections->gap_index[i];

        if (IsHorizontalGap(Gap))
        {
            temp = DataGrid->vertically->coordinates[index].solution->constraints->used_index;

            if (DataGrid->vertically->coordinates[index].solution->filled == false)
            {
                if (GetWord(DataGrid->vertically->coordinates[index], Dictionary) == NULL)
                {
                    DataGrid->vertically->coordinates[index].solution->constraints->used_index = temp;
                    return false;
                }
                else
                    DataGrid->vertically->coordinates[index].solution->constraints->used_index = temp;
            }
        }
        else
        {
            temp = DataGrid->horizontally->coordinates[index].solution->constraints->used_index;

            if (DataGrid->horizontally->coordinates[index].solution->filled == false)
            {
                if (GetWord(DataGrid->horizontally->coordinates[index], Dictionary) == NULL)
                {
                    DataGrid->horizontally->coordinates[index].solution->constraints->used_index = temp;
                    return false;
                }   
                else
                    DataGrid->horizontally->coordinates[index].solution->constraints->used_index = temp;
            }
        }   
    }
    return true;
}

Vector SetWordsVector(struct GridCOORDINATES Gap, HashTable Dictionary)
{
    int index, possibiities = INT_MAX;
    bool has_constraints = false;
    char letter, ch;

    for (int i = 0; i < Gap.length; i++)
    {
        ch = Gap.solution->constraints->letters[i];
        
        if (ch == ' ')  
            continue;
        
        if (Dictionary->length[Gap.length]->position[i]->letter[(int)(ch)-97]->words->size < possibiities)
        {
            possibiities = Dictionary->length[Gap.length]->position[i]->letter[(int)(ch)-97]->words->size;
            index = i;
            letter = ch;
            has_constraints = true;
        }
    }

    if (has_constraints == false)
        return Dictionary->length[Gap.length]->words;
    else
        return Dictionary->length[Gap.length]->position[index]->letter[(int)(letter)-97]->words;
}

int GetWordsNumber(struct GridCOORDINATES Gap, HashTable Dictionary)
{
    Vector words_vector = SetWordsVector(Gap, Dictionary);
    int count = 0;
    bool suitable;

    for (int i = 0; i < words_vector->size; i++)
    {
        suitable = true;

        for (int j = 0; j < Gap.length; j++)
        {
            if (Gap.solution->constraints->letters[j] == ' ')
                continue;
            if (Gap.solution->constraints->letters[j] != words_vector->word[i][j])
                suitable = false;
        }
        if (suitable == true)   
            count++;
    }
    return count;
}

String GetWord(struct GridCOORDINATES Gap, HashTable Dictionary)
{
    Vector words_vector;
    bool suitable;

    if (Gap.solution->constraints->used_index == -1)
    {
        words_vector = SetWordsVector(Gap, Dictionary);
        Gap.solution->constraints->words = words_vector;
    }
    else
        words_vector = Gap.solution->constraints->words;

    for (int i = Gap.solution->constraints->used_index+1; i < words_vector->size; i++)
    {
        suitable = true;

        for (int j = 0; j < Gap.length; j++)
        {
            if (Gap.solution->constraints->letters[j] == ' ')
                continue;
            if (Gap.solution->constraints->letters[j] != words_vector->word[i][j])
                suitable = false;
        }
        
        if (suitable == true)
        {
            Gap.solution->constraints->used_index = i;
            return words_vector->word[i];
        }
    }
    Gap.solution->constraints->used_index = -1;
    return NULL;
}

Grid PlaceWord(Grid DataGrid, struct GridCOORDINATES Gap, char* Word)
{
    strcpy(Gap.solution->word, Word);
    Gap.solution->filled = true;

    if(Gap.solution->backtracking == true)
        Gap.solution->backtracking = false;

    DataGrid = AddConstraints(DataGrid, Gap);
    FLAG++;

    return DataGrid;
}

Grid Backtracking(Grid DataGrid, struct GridCOORDINATES Gap, Flags* Flags, int CurrentFlag)
{
    struct GridCOORDINATES faulty;

    faulty = GetFaultyGap(DataGrid, Gap, Flags, CurrentFlag);
    DataGrid = RemoveWord(DataGrid, faulty);
    FLAG = faulty.flag;

    return DataGrid;
}

struct GridCOORDINATES GetFaultyGap(Grid DataGrid, struct GridCOORDINATES Gap, Flags* Flags, int CurrentFlag)
{
    if (Flags[CurrentFlag-1]->horizontal_gap == true)
        return DataGrid->horizontally->coordinates[Flags[CurrentFlag-1]->index];
    else    
        return DataGrid->vertically->coordinates[Flags[CurrentFlag-1]->index];
}

Grid AddConstraints(Grid DataGrid, struct GridCOORDINATES Gap)
{
    if(IsHorizontalGap(Gap))
        DataGrid = AddConstraintsVertically(DataGrid, Gap);
    else
        DataGrid = AddConstraintsHorizontally(DataGrid, Gap); 
    return DataGrid;    
}

Grid RemoveConstraints(Grid DataGrid, struct GridCOORDINATES Gap)
{
    if(IsHorizontalGap(Gap))
        DataGrid = RemoveConstraintsVertically(DataGrid, Gap);
    else
        DataGrid = RemoveConstraintsHorizontally(DataGrid, Gap);
    return DataGrid;  
}

Grid AddConstraintsHorizontally(Grid DataGrid, struct GridCOORDINATES Gap)
{
    int gap_index, row_index, col_index, temp, start;
    
    row_index = Gap.start_row;
    col_index = Gap.start_col;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        gap_index = Gap.intersections->gap_index[i];
        start = DataGrid->horizontally->coordinates[gap_index].start_col;
        temp = DataGrid->horizontally->coordinates[gap_index].start_row;
        
        DataGrid->horizontally->coordinates[gap_index].solution->constraints->letters[col_index-start] = Gap.solution->word[temp-row_index];
    }
    return DataGrid;
}

Grid AddConstraintsVertically(Grid DataGrid, struct GridCOORDINATES Gap)
{
    int gap_index, row_index, col_index, temp, start;
    
    row_index = Gap.start_row;
    col_index = Gap.start_col;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        gap_index = Gap.intersections->gap_index[i];
        start = DataGrid->vertically->coordinates[gap_index].start_row;
        temp = DataGrid->vertically->coordinates[gap_index].start_col;
            
        DataGrid->vertically->coordinates[gap_index].solution->constraints->letters[row_index-start] = Gap.solution->word[temp-col_index];  
    }
    return DataGrid;
}

Grid RemoveConstraintsHorizontally(Grid DataGrid, struct GridCOORDINATES Gap)
{
    int gap_index, col_index, start;
    col_index = Gap.start_col;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        gap_index = Gap.intersections->gap_index[i];
        start = DataGrid->horizontally->coordinates[gap_index].start_col; 
        DataGrid->horizontally->coordinates[gap_index].solution->constraints->letters[col_index-start] = ' ';  
    }
    return DataGrid;
}

Grid RemoveConstraintsVertically(Grid DataGrid, struct GridCOORDINATES Gap)
{
    int gap_index, row_index, temp, start;
    row_index = Gap.start_row;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        gap_index = Gap.intersections->gap_index[i];
        start = DataGrid->vertically->coordinates[gap_index].start_row;
        DataGrid->vertically->coordinates[gap_index].solution->constraints->letters[row_index-start] = ' ';  
    }
    return DataGrid;
}

Grid RemoveWord(Grid DataGrid, struct GridCOORDINATES Gap)
{
    Gap.solution->filled = false;
    
    for(int i = 0; i < Gap.length; i++)
        Gap.solution->word[i] = ' ';

    DataGrid = RemoveConstraints(DataGrid, Gap);
    return DataGrid;    
}

int IsHorizontalGap(struct GridCOORDINATES Gap)
{
    return (Gap.start_row == Gap.end_row);
}