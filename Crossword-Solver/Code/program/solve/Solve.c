#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "../../include/solve/Solve.h"

int FLAG;
int COUNT1;
int COUNT2;
int COUNT3;

Grid Solve(Grid DataGrid, HashTable Dictionary)
{
    Flags* flags;
    FLAG = 0;
    COUNT1 = 0;
    COUNT2 = 0;
    COUNT3 = 0;

    DataGrid = Sort(DataGrid);
    Initialize(DataGrid, Dictionary);
    flags = FlagsInitialize(DataGrid, flags);

    DataGrid = IntersectionsHorizontally(DataGrid);
    DataGrid = IntersectionsVertically(DataGrid);

    DataGrid = SetGapsFillingOrder(DataGrid, flags);
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
        Flags[i] = malloc(sizeof(struct CrosswordFLAGS));

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

Grid SetGapsFillingOrder(Grid DataGrid, Flags* Flags)
{
    int words_horizontally, words_vertically, max, count, flag;
    count = 0; 
    flag = 0;

    words_horizontally = DataGrid->horizontally->words_count;
    words_vertically = DataGrid->vertically->words_count;
    max = MAX(words_horizontally, words_vertically);
        
    for(int i = 0; i < max; i++)
    {
        if((count < words_horizontally) && (count < words_vertically))
        {
            Flags[flag]->horizontal_gap = true;
            Flags[flag]->index = i;
            DataGrid->horizontally->coordinates[i].flag = flag++;

            Flags[flag]->horizontal_gap = false;
            Flags[flag]->index = i;
            DataGrid->vertically->coordinates[i].flag = flag++;
            count++;
        }
        else
        {
            if(words_horizontally > words_vertically)
            {
                Flags[flag]->horizontal_gap = true;
                Flags[flag]->index = i;
                DataGrid->horizontally->coordinates[i].flag = flag++;
            }         
            else
            {
                Flags[flag]->horizontal_gap = false;
                Flags[flag]->index = i;
                DataGrid->vertically->coordinates[i].flag = flag++;
            }
        }
    }
    return DataGrid;
}

Grid SolveCrossword(Grid DataGrid, HashTable Dictionary, Flags* Flags)
{
    int max_flag = DataGrid->horizontally->words_count + DataGrid->vertically->words_count - 1;

    //while (FLAG != max_flag+1)
    for(int i = 0; i < 50000000; i++)
    {
        if(FLAG == max_flag+1)
            break;
        DataGrid = GetGapToFill(DataGrid, Dictionary, Flags, FLAG);
    }
    printf("COUNT1 %d COUNT2 %d COUNT3 %d\n", COUNT1, COUNT2, COUNT3);
    return DataGrid;
}

Grid GetGapToFill(Grid DataGrid, HashTable Dictionary, Flags* Flags, int CurrentFlag)
{
    int index;

    if (Flags[CurrentFlag]->horizontal_gap == true)
    {
        index = Flags[CurrentFlag]->index;
        DataGrid = ChooseWordToFillGap(DataGrid, DataGrid->horizontally->coordinates[index], Dictionary, Flags, CurrentFlag);
    }
    else 
    {
        index = Flags[CurrentFlag]->index;
        DataGrid = ChooseWordToFillGap(DataGrid, DataGrid->vertically->coordinates[index], Dictionary, Flags, CurrentFlag);
    }
    return DataGrid;
}

Grid ChooseWordToFillGap(Grid DataGrid, struct GridCOORDINATES Gap, HashTable Dictionary, Flags* Flags, int CurrentFlag)
{
    char* word = malloc(100 * sizeof(char));
    Vector words_vector;
    int index;
    
    word = GetWord(Gap, Dictionary);

    if (word == NULL)
    {
        DataGrid = Backtracking(DataGrid, Gap, Flags, CurrentFlag);
    }
    else
    {
        DataGrid = PlaceWord(DataGrid, Gap, word);
    }
    return DataGrid;
}

bool IsValid(Grid DataGrid, struct GridCOORDINATES Gap, HashTable Dictionary)
{
    int index;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        index = Gap.intersections->gap_index[i];

        if (IsHorizontalGap(Gap))
        {
            if (GetWord(DataGrid->vertically->coordinates[index], Dictionary) == NULL)
                return false;
        }
        else
        {
            if (GetWord(DataGrid->horizontally->coordinates[index], Dictionary) == NULL)
                return false;
        }   
    }
    return true;
}

Vector SetWordsVector(struct GridCOORDINATES Gap, HashTable Dictionary)
{
    int index, possibiities = INT_MAX;
    char letter, ch;
    bool has_constraints = false;

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
        COUNT3++;
    }

    if (has_constraints == false)
        return Dictionary->length[Gap.length]->words;
    else
        return Dictionary->length[Gap.length]->position[index]->letter[(int)(letter)-97]->words;
}

String GetWord(struct GridCOORDINATES Gap, HashTable Dictionary)
{
    Vector words_vector = malloc(sizeof(struct VECTOR));
    bool suitable;

    if (Gap.solution->constraints->used_index == -1)
    {
        words_vector = SetWordsVector(Gap, Dictionary);
        Gap.solution->constraints->words = words_vector;
    }
    else
    {
        words_vector = Gap.solution->constraints->words;
    }

    for (int i = Gap.solution->constraints->used_index+1; i < words_vector->size; i++)
    {
        suitable = true;
        COUNT1++;

        for (int j = 0; j < Gap.length; j++)
        {
            COUNT2++;
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
    DataGrid = RemoveAffectedWords(DataGrid, Gap);
    FLAG = faulty.flag;

    return DataGrid;
}

struct GridCOORDINATES GetFaultyGap(Grid DataGrid, struct GridCOORDINATES Gap, Flags* Flags, int CurrentFlag)
{
    struct GridCOORDINATES faulty;
    int index;

    for(int i = CurrentFlag-1; i >= 0; i--)
    {
        if ((Flags[i]->horizontal_gap == true) && (!IsHorizontalGap(Gap)))
        {
            index = Flags[i]->index;
            return DataGrid->horizontally->coordinates[index];
        }
            
        if (Flags[i]->horizontal_gap == false && (IsHorizontalGap(Gap)))
        {
            index = Flags[i]->index;
            return DataGrid->vertically->coordinates[index];
        }
    }
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

Grid RemoveAffectedWords(Grid DataGrid, struct GridCOORDINATES Gap)
{
    int index;

    if(IsHorizontalGap(Gap))
    {
        for (int i = 0; i < Gap.intersections->num; i++)
        {
            index = Gap.intersections->gap_index[i];

            if (DataGrid->vertically->coordinates[index].flag > Gap.flag && DataGrid->vertically->coordinates[index].solution->filled == true)
                DataGrid = RemoveWord(DataGrid, DataGrid->vertically->coordinates[index]);
        }
    }
    else
    {
        for (int i = 0; i < Gap.intersections->num; i++)
        {
            index = Gap.intersections->gap_index[i];

            if(DataGrid->horizontally->coordinates[index].flag > Gap.flag && DataGrid->horizontally->coordinates[index].solution->filled == true)
                DataGrid = RemoveWord(DataGrid, DataGrid->horizontally->coordinates[index]);
        }
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