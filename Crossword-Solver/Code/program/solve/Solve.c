#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "../../include/solve/Solve.h"

#define MAX(x,y) (((x) > (y)) ? (x) : (y)) 

int FLAG;

Grid Solve(Grid DataGrid, HashTable Dictionary)
{
    DataGrid = Sort(DataGrid);
    Initialize(DataGrid, Dictionary);
    FLAG = 0;

    DataGrid = IntersectionsHorizontally(DataGrid);
    DataGrid = IntersectionsVertically(DataGrid);

    Flags* flags_link;

    flags_link = malloc((DataGrid->horizontally->words_count + DataGrid->vertically->words_count) * sizeof(Flags));
    for (int i = 0; i < (DataGrid->horizontally->words_count + DataGrid->vertically->words_count); i++)
        flags_link[i] = malloc(sizeof(struct CrosswordFLAGS));

    //DataGrid = SetFlags(DataGrid, flags_link);
    DataGrid = SetGapsFillingOrder(DataGrid, flags_link);
    DataGrid = FillGaps(DataGrid, Dictionary, flags_link);

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
        DataGrid->horizontally->coordinates[i].solution->word_placed = malloc((length+1) * sizeof(char));
        DataGrid->horizontally->coordinates[i].solution->filled = false;
        DataGrid->horizontally->coordinates[i].solution->backtracking = false;

        // we assume at first that we have no constraints
        DataGrid->horizontally->coordinates[i].solution->constraints = false;

        DataGrid->horizontally->coordinates[i].solution->no_constraints = malloc(sizeof(struct Crossword_NO_CONSTRAINTS));
        DataGrid->horizontally->coordinates[i].solution->no_constraints->words = Dictionary->length[length]->words; 
        DataGrid->horizontally->coordinates[i].solution->no_constraints->used_index = -1;
        
        // basic memory allocation in case we have constraints
        DataGrid->horizontally->coordinates[i].solution->has_constraints = malloc(sizeof(struct CrosswordCONSTRAINTS));
        DataGrid->horizontally->coordinates[i].solution->has_constraints->constrained_letter = malloc((length+1) * sizeof(bool));
        DataGrid->horizontally->coordinates[i].solution->has_constraints->constraints = malloc((length+1) * sizeof(char));
        DataGrid->horizontally->coordinates[i].solution->has_constraints->words = malloc(sizeof(struct VECTOR));
        DataGrid->horizontally->coordinates[i].solution->has_constraints->words = VectorInitialize(DataGrid->horizontally->coordinates[i].solution->has_constraints->words);

        for(int j = 0; j < length; j++)
        {
            DataGrid->horizontally->coordinates[i].solution->word_placed[j] = ' ';
            DataGrid->horizontally->coordinates[i].solution->has_constraints->constraints[j] = false;
            DataGrid->horizontally->coordinates[i].solution->has_constraints->constrained_letter[j] = false;
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
        DataGrid->vertically->coordinates[i].solution->word_placed = malloc((length+1) * sizeof(char));
        DataGrid->vertically->coordinates[i].solution->backtracking = false;
        DataGrid->vertically->coordinates[i].solution->filled = false;

        // we assume at first that we have no constraints
        DataGrid->vertically->coordinates[i].solution->constraints = false;

        DataGrid->vertically->coordinates[i].solution->no_constraints = malloc(sizeof(struct Crossword_NO_CONSTRAINTS));
        DataGrid->vertically->coordinates[i].solution->no_constraints->words = Dictionary->length[length]->words; 
        DataGrid->vertically->coordinates[i].solution->no_constraints->used_index = -1;

        // basic memory allocation in case we have constraints 
        DataGrid->vertically->coordinates[i].solution->has_constraints = malloc(sizeof(struct CrosswordCONSTRAINTS));
        DataGrid->vertically->coordinates[i].solution->has_constraints->constrained_letter = malloc((length+1) * sizeof(bool));
        DataGrid->vertically->coordinates[i].solution->has_constraints->constraints = malloc((length+1) * sizeof(char));
        DataGrid->vertically->coordinates[i].solution->has_constraints->words = malloc(sizeof(struct VECTOR));
        DataGrid->vertically->coordinates[i].solution->has_constraints->words = VectorInitialize(DataGrid->vertically->coordinates[i].solution->has_constraints->words);

        for(int j = 0; j < length; j++)
        {
            DataGrid->vertically->coordinates[i].solution->word_placed[j] = ' ';
            DataGrid->vertically->coordinates[i].solution->has_constraints->constraints[j] = ' ';
            DataGrid->vertically->coordinates[i].solution->has_constraints->constrained_letter[j] = false;
        }
    }
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

Grid SetGapsFillingOrder(Grid DataGrid, Flags* FlagLink)
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
            FlagLink[flag]->horizontal_gap = true;
            FlagLink[flag]->index = i;
            DataGrid->horizontally->coordinates[i].flag = flag++;

            FlagLink[flag]->horizontal_gap = false;
            FlagLink[flag]->index = i;
            DataGrid->vertically->coordinates[i].flag = flag++;
            count++;
        }
        else
        {
            if(words_horizontally > words_vertically)
            {
                FlagLink[flag]->horizontal_gap = true;
                FlagLink[flag]->index = i;
                DataGrid->horizontally->coordinates[i].flag = flag++;
            }         
            else
            {
                FlagLink[flag]->horizontal_gap = false;
                FlagLink[flag]->index = i;
                DataGrid->vertically->coordinates[i].flag = flag++;
            }
        }
    }
    return DataGrid;
}

Grid FillGaps(Grid DataGrid, HashTable Dictionary, Flags* FlagsLink)
{
    int max_flag = DataGrid->horizontally->words_count + DataGrid->vertically->words_count - 1;

    //while (FLAG != max_flag+1)
    for(int i = 0; i < 1000; i++)
    {
        if(FLAG == max_flag+1)
            break;
        DataGrid = GetGapToFill(DataGrid, Dictionary, FLAG, FlagsLink);
    }
    return DataGrid;
}

Grid SetFlags(Grid DataGrid, Flags* FlagsLink)
{
    int words_horizontally, words_vertically, min1, min2, index1, index2, min, index, hold, flag, max_flag;
    
    words_horizontally = DataGrid->horizontally->words_count;
    words_vertically = DataGrid->vertically->words_count;
    max_flag = words_horizontally + words_vertically-1;
    min1 = INT_MAX;
    min2 = INT_MAX;
    flag = 0;

    for (int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        if (DataGrid->horizontally->coordinates[i].word_possibilities < min1)
        {
            min1 = DataGrid->horizontally->coordinates[i].word_possibilities;
            index1 = i;
        }
    }

    for (int i = 0; i < DataGrid->vertically->words_count; i++)
    {
        if (DataGrid->vertically->coordinates[i].word_possibilities < min2)
        {
            min2 = DataGrid->vertically->coordinates[i].word_possibilities;
            index2 = i;
        }
    }
   
    if (min1 <= min2)
    {
        FlagsLink[flag]->horizontal_gap = true;
        FlagsLink[flag]->index = index1;
        DataGrid->horizontally->coordinates[index1].flag = flag++;
    }
    else 
    {
        FlagsLink[flag]->horizontal_gap = false;
        FlagsLink[flag]->index = index2;        
        DataGrid->vertically->coordinates[index2].flag = flag++;
    }

    while (flag <= max_flag)
    {
        if (min1 <= min2)
        {
            min = INT_MAX;
            hold = INT_MAX;

            for (int j = 0; j < DataGrid->horizontally->coordinates[index1].intersections->num; j++)
            {
                index = DataGrid->horizontally->coordinates[index1].intersections->gap_index[j];

                if (DataGrid->vertically->coordinates[index].word_possibilities < min && DataGrid->vertically->coordinates[index].flag == INT_MAX)
                {
                    min = DataGrid->vertically->coordinates[index].word_possibilities;
                    hold = index;
                }
            }
            if (hold == INT_MAX)
                hold = index;
            if (DataGrid->vertically->coordinates[hold].flag == INT_MAX)
            {
                FlagsLink[flag]->horizontal_gap = false;
                FlagsLink[flag]->index = hold;
                DataGrid->vertically->coordinates[hold].flag = flag++;
            }

            min = INT_MAX;

            for (int j = 0; j < DataGrid->vertically->coordinates[hold].intersections->num; j++)
            {
                index = DataGrid->vertically->coordinates[hold].intersections->gap_index[j];

                if (DataGrid->horizontally->coordinates[index].word_possibilities < min && DataGrid->horizontally->coordinates[index].flag == INT_MAX)
                {
                    min = DataGrid->horizontally->coordinates[index].word_possibilities;
                    hold = index;
                }
            }
            if (hold == INT_MAX)
                hold = index;
            if (DataGrid->horizontally->coordinates[hold].flag == INT_MAX)
            {
                FlagsLink[flag]->horizontal_gap = true;
                FlagsLink[flag]->index = hold;
                DataGrid->horizontally->coordinates[hold].flag = flag++;
            }
            index1 = hold;    
        }
        else
        {
            min = INT_MAX;
            hold = INT_MAX;

            for (int j = 0; j < DataGrid->vertically->coordinates[index2].intersections->num; j++)
            {
                index = DataGrid->vertically->coordinates[index2].intersections->gap_index[j];

                if (DataGrid->horizontally->coordinates[index].word_possibilities < min && DataGrid->horizontally->coordinates[index].flag == INT_MAX)
                {
                    min = DataGrid->horizontally->coordinates[index].word_possibilities;
                    hold = index;
                }
            }
            if (hold == INT_MAX)
                hold = index;
            if (DataGrid->horizontally->coordinates[hold].flag == INT_MAX)
            {
                FlagsLink[flag]->horizontal_gap = true;
                FlagsLink[flag]->index = hold;
                DataGrid->horizontally->coordinates[hold].flag = flag++;
            }

            min = INT_MAX;

            for (int j = 0; j < DataGrid->horizontally->coordinates[hold].intersections->num; j++)
            {
                index = DataGrid->horizontally->coordinates[hold].intersections->gap_index[j];

                if (DataGrid->vertically->coordinates[index].word_possibilities < min && DataGrid->vertically->coordinates[index].flag == INT_MAX)
                {
                    min = DataGrid->vertically->coordinates[index].word_possibilities;
                    hold = index;
                }
            }
            if (hold == INT_MAX)
                hold = index;
            if (DataGrid->vertically->coordinates[hold].flag == INT_MAX)
            {
                FlagsLink[flag]->horizontal_gap = false;
                FlagsLink[flag]->index = hold;
                DataGrid->vertically->coordinates[hold].flag = flag++;
            }
            index2 = hold;        
        }
    }

    for (int i = 0; i < DataGrid->horizontally->words_count; i++)
    {
        printf("Flag is %d row %d\n", DataGrid->horizontally->coordinates[i].flag, DataGrid->horizontally->coordinates[i].start_row);
    }
    for (int i = 0; i < DataGrid->vertically->words_count; i++)
    {
        printf("Flag is %d col %d\n", DataGrid->vertically->coordinates[i].flag, DataGrid->vertically->coordinates[i].start_col);
    }
    
    return DataGrid;
}

Grid GetGapToFill(Grid DataGrid, HashTable Dictionary, int flag, Flags* FlagsLink)
{
    char* word = malloc(100 * sizeof(char));
    int index;

    if (FlagsLink[flag]->horizontal_gap == true)
    {
        index = FlagsLink[flag]->index;
        DataGrid = ChooseWordToFillGap(DataGrid, DataGrid->horizontally->coordinates[index], Dictionary, word);
    }
    else 
    {
        index = FlagsLink[flag]->index;
        DataGrid = ChooseWordToFillGap(DataGrid, DataGrid->vertically->coordinates[index], Dictionary, word);
    }
    return DataGrid;
}

Grid ChooseWordToFillGap(Grid DataGrid, struct Grid_WORD_COORDINATES Gap, HashTable Dictionary, char* Word)
{
    int index;

    if(GapHasConstraints(Gap))
    {
        if(VectorEmpty(Gap.solution->has_constraints->words))
        {
            if(Gap.solution->backtracking == false)
            {
                Gap = PutWordsOnVector(Gap, Dictionary);

                if(VectorEmpty(Gap.solution->has_constraints->words))
                {
                    DataGrid = Backtracking(DataGrid, Gap, Dictionary);
                    return DataGrid;
                }
            }
            else
            {
                Gap.solution->backtracking = false;
                DataGrid = Backtracking(DataGrid, Gap, Dictionary);
                return DataGrid;
            }
        }
        Gap.solution->has_constraints->words = VectorRemove(Gap.solution->has_constraints->words, Word);
        DataGrid = PlaceWord(DataGrid, Gap, Word);
    }
    else
    {
        Gap.solution->no_constraints->used_index++;

        if(Gap.solution->no_constraints->used_index >= Gap.solution->no_constraints->words->size)
        {
            DataGrid = Backtracking(DataGrid, Gap, Dictionary);
            return DataGrid;
        }
        index = Gap.solution->no_constraints->used_index;
        strcpy(Word, Gap.solution->no_constraints->words->word[index]);
        DataGrid = PlaceWord(DataGrid, Gap, Word);
    }
    return DataGrid;
}

struct Grid_WORD_COORDINATES PutWordsOnVector(struct Grid_WORD_COORDINATES Gap, HashTable Dictionary)
{
    Vector words;
    char c;
    bool suitable;
    Vector vector = Gap.solution->has_constraints->words;

    for(int i = 0; i < Gap.length; i++)
    {
        if(Gap.solution->constraints == true)
        {
            if(Gap.solution->has_constraints->constrained_letter[i] == true)
            {
                c = Gap.solution->has_constraints->constraints[i];
                words = Dictionary->length[Gap.length]->position[i]->letter[(int)(c)-97]->words;
                break;
            }
        }
    }      

    for(int i = 0; i < words->size; i++)
    {
        suitable = true;

        for(int j = 0; j < Gap.length; j++)
        {
            if((Gap.solution->has_constraints->constrained_letter[j] == true) && (Gap.solution->has_constraints->constraints[j] != words->word[i][j]))
                suitable = false;
        }
        if(suitable == true)
            vector = VectorInsert(vector, words->word[i]);
    }
    Gap.solution->has_constraints->words = vector;
    return Gap;
}

void ForwardCheck()
{
    
}

bool GapHasConstraints(struct Grid_WORD_COORDINATES Gap)
{
    return (Gap.solution->constraints == true);
}

Grid PlaceWord(Grid DataGrid, struct Grid_WORD_COORDINATES Gap, char* Word)
{
    for(int i = 0; i < strlen(Word); i++)
    {
        Gap.solution->word_placed[i] = Word[i];
        Gap.solution->filled = true;
    }
    if(Gap.solution->backtracking == true)
        Gap.solution->backtracking = false;

    DataGrid = AddConstraints(DataGrid, Gap);
    FLAG++;

    return DataGrid;
}

Grid AddConstraints(Grid DataGrid, struct Grid_WORD_COORDINATES Gap)
{
    if(IsHorizontalGap(Gap))
        DataGrid = AddConstraintsVertically(DataGrid, Gap);
    else
        DataGrid = AddConstraintsHorizontally(DataGrid, Gap); 
    
    return DataGrid;    
}

Grid RemoveConstraints(Grid DataGrid, struct Grid_WORD_COORDINATES Gap)
{
    if(IsHorizontalGap(Gap))
        DataGrid = RemoveConstraintsVertically(DataGrid, Gap);
    else
        DataGrid = RemoveConstraintsHorizontally(DataGrid, Gap);

    return DataGrid;  
}

Grid AddConstraintsHorizontally(Grid DataGrid, struct Grid_WORD_COORDINATES Gap)
{
    int gap_index, row_index, col_index, temp, start;
    
    row_index = Gap.start_row;
    col_index = Gap.start_col;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        gap_index = Gap.intersections->gap_index[i];

        if (DataGrid->horizontally->coordinates[gap_index].solution->filled == false)
        {
            start = DataGrid->horizontally->coordinates[gap_index].start_col;
            temp = DataGrid->horizontally->coordinates[gap_index].start_row;

            DataGrid->horizontally->coordinates[gap_index].solution->constraints = true;
            DataGrid->horizontally->coordinates[gap_index].solution->has_constraints->constraints[col_index-start] = Gap.solution->word_placed[temp-row_index];
            DataGrid->horizontally->coordinates[gap_index].solution->has_constraints->constrained_letter[col_index-start] = true;
        }
    }
    return DataGrid;
}

Grid AddConstraintsVertically(Grid DataGrid, struct Grid_WORD_COORDINATES Gap)
{
    int gap_index, row_index, col_index, temp, start, end;
    
    row_index = Gap.start_row;
    col_index = Gap.start_col;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        gap_index = Gap.intersections->gap_index[i];

        if (DataGrid->vertically->coordinates[gap_index].solution->filled == false)
        {
            start = DataGrid->vertically->coordinates[gap_index].start_row;
            end = DataGrid->vertically->coordinates[gap_index].end_row; 
            temp = DataGrid->vertically->coordinates[gap_index].start_col;
            
            DataGrid->vertically->coordinates[gap_index].solution->constraints = true;
            DataGrid->vertically->coordinates[gap_index].solution->has_constraints->constraints[row_index-start] = Gap.solution->word_placed[temp-col_index];  
            DataGrid->vertically->coordinates[gap_index].solution->has_constraints->constrained_letter[row_index-start] = true;
        }
    }
    return DataGrid;
}

Grid RemoveConstraintsHorizontally(Grid DataGrid, struct Grid_WORD_COORDINATES Gap)
{
    int gap_index, col_index, start;
    bool no_constraints;

    col_index = Gap.start_col;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        gap_index = Gap.intersections->gap_index[i];

        start = DataGrid->horizontally->coordinates[gap_index].start_col;
        no_constraints = true;
 
        DataGrid->horizontally->coordinates[gap_index].solution->has_constraints->constraints[col_index-start] = ' ';  
        DataGrid->horizontally->coordinates[gap_index].solution->has_constraints->constrained_letter[col_index-start] = false;

        for(int k = 0; k < DataGrid->horizontally->coordinates[gap_index].length; k++)
        {
            if(DataGrid->horizontally->coordinates[gap_index].solution->has_constraints->constrained_letter[k] == true)
                    no_constraints = false;
        }
        if(no_constraints)
            DataGrid->horizontally->coordinates[gap_index].solution->constraints = false;  
    }
    return DataGrid;
}

Grid RemoveConstraintsVertically(Grid DataGrid, struct Grid_WORD_COORDINATES Gap)
{
    int gap_index, row_index, col1_index, col2_index, temp, start, end;
    bool no_constraints;

    row_index = Gap.start_row;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        gap_index = Gap.intersections->gap_index[i];

        start = DataGrid->vertically->coordinates[gap_index].start_row;
        end = DataGrid->vertically->coordinates[gap_index].end_row;
        temp = DataGrid->vertically->coordinates[gap_index].start_col;
        no_constraints = true;

        DataGrid->vertically->coordinates[gap_index].solution->has_constraints->constraints[row_index-start] = ' ';  
        DataGrid->vertically->coordinates[gap_index].solution->has_constraints->constrained_letter[row_index-start] = false;
            
        for(int k = 0; k < DataGrid->vertically->coordinates[gap_index].length; k++)
        {
            if(DataGrid->vertically->coordinates[gap_index].solution->has_constraints->constrained_letter[k] == true)
                no_constraints = false;
        }
        if(no_constraints)
            DataGrid->vertically->coordinates[gap_index].solution->constraints = false;
    }
    return DataGrid;
}

Grid Backtracking(Grid DataGrid, struct Grid_WORD_COORDINATES Gap, HashTable Dictionary)
{
    struct Grid_WORD_COORDINATES faulty;

    faulty = GetFaultyGap(DataGrid, Gap);
    faulty.solution->backtracking = true;
    
    DataGrid = RemoveWord(DataGrid, faulty);
    DataGrid = RemoveAffectedWords(DataGrid, Gap);
    FLAG = faulty.flag;

    return DataGrid;
}

Grid RemoveWord(Grid DataGrid, struct Grid_WORD_COORDINATES Gap)
{
    Gap.solution->filled = false;
    
    for(int i = 0; i < Gap.length; i++)
        Gap.solution->word_placed[i] = ' ';

    DataGrid = RemoveConstraints(DataGrid, Gap);
    return DataGrid;    
}

Grid RemoveAffectedWords(Grid DataGrid, struct Grid_WORD_COORDINATES Gap)
{
    if(IsHorizontalGap(Gap))
    {
        for(int i = DataGrid->vertically->words_count-1; i > Gap.flag ; i--)
        {
            if(DataGrid->vertically->coordinates[i].flag > Gap.flag && DataGrid->vertically->coordinates[i].solution->filled == true)
                DataGrid = RemoveWord(DataGrid, DataGrid->vertically->coordinates[i]);
        }
    }
    else
    {
        for(int i = DataGrid->horizontally->words_count-1; i > Gap.flag ; i--)
        {
            if(DataGrid->horizontally->coordinates[i].flag > Gap.flag)
                DataGrid = RemoveWord(DataGrid, DataGrid->horizontally->coordinates[i]);
        }
    }
    return DataGrid;
}

struct Grid_WORD_COORDINATES GetFaultyGap(Grid DataGrid, struct Grid_WORD_COORDINATES Gap)
{
    struct Grid_WORD_COORDINATES faulty;

    if(IsHorizontalGap(Gap)) // the faulty gap is vertical 
    {
        for(int i = 0; i < DataGrid->vertically->words_count; i++)
        {
            if(DataGrid->vertically->coordinates[i].flag < Gap.flag)
                faulty = DataGrid->vertically->coordinates[i];
        }    
        return faulty;
    }
    else    // the faulty gap is horizontal
    {
        for(int i = 0; i < DataGrid->horizontally->words_count; i++)
        {
            if(DataGrid->horizontally->coordinates[i].flag < Gap.flag)
                faulty = DataGrid->horizontally->coordinates[i];
        }
        return faulty;
    }
}

int IsHorizontalGap(struct Grid_WORD_COORDINATES Gap)
{
    return (Gap.start_row == Gap.end_row);
}