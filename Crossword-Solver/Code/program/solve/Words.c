#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "../../include/solve/Words.h"

bool IsWordAcceptable(DataGrid DataGrid, Coordinates Gap, HashTable Dictionary)
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
                if (!FindSuitableWord(&(DataGrid.vertically->gap[index]), Dictionary))
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
                if (!FindSuitableWord(&(DataGrid.horizontally->gap[index]), Dictionary))
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

Words AttachDictionary(Coordinates Gap, HashTable Dictionary)
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

int GetNumberOfSuitableWords(Coordinates Gap, HashTable Dictionary)
{
    Words dictionary = AttachDictionary(Gap, Dictionary);
    int count = 0;
    bool suitable;

    for (int i = 0; i < dictionary.size; i++)
    {
        suitable = true;

        for (int j = 0; j < Gap.length; j++)
        {
            if (Gap.constraints[j] == ' ')
                continue;
            if (Gap.constraints[j] != dictionary.word[i][j])
                suitable = false;
        }
        if (suitable == true)   
            count++;
    }
    return count;
}

String FindSuitableWord(Coordinates* Gap, HashTable Dictionary)
{
    Words* dictionary = malloc(sizeof(Vector));
    bool suitable;

    if (Gap->index == -1)
    {
        *dictionary = AttachDictionary(*Gap, Dictionary);
        Gap->words_vector = dictionary;
    }
    else
        dictionary = Gap->words_vector;

    for (int i = Gap->index+1; i < dictionary->size; i++)
    {
        suitable = true;

        for (int j = 0; j < Gap->length; j++)
        {
            if (Gap->constraints[j] == ' ')
                continue;
            if (Gap->constraints[j] != dictionary->word[i][j])
                suitable = false;
        }
        
        if (suitable == true)
        {
            Gap->index = i;
            return dictionary->word[i];
        }
    }
    Gap->index = -1;
    return NULL;
}

void PlaceWord(DataGrid* DataGrid, Coordinates* Gap, String Word, int *FLAG)
{
    Gap->filled = true;
    strcpy(Gap->word, Word);

    AddConstraints(DataGrid, *Gap);
    (*FLAG)++;
}