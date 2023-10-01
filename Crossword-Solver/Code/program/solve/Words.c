#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "../../include/solve/Words.h"

bool IsWordAcceptable(DataGrid DataGrid, Coordinates Gap, HashTable Dictionary)
{
    int index, temp;

    for (int i = 0; i < Gap.intersections->num; i++)
    {
        // the index of the interseected gap
        index = Gap.intersections->gap_index[i];

        if (IsHorizontalGap(Gap))                         
        {
            temp = DataGrid.vertically->gap[index].index;

            // if the gap is filled, new constraints cannot be set
            if (!DataGrid.vertically->gap[index].filled)    
            {
                // not suitable word can be found
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
            // the index of the interseected gap
            temp = DataGrid.horizontally->gap[index].index;

            // if the gap is filled, new constraints cannot be set
            if (!DataGrid.horizontally->gap[index].filled)
            {
                // not suitable word can be found
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
        // ch represents a constrained letter 
        ch = Gap.constraints[i];
        
        if (ch == ' ')  // free letter
            continue;
        
        // we try to find the best possible vector with constrained words, in terms of possibilities
        // the dictionary offers a vector of words with only one constraint at the time
        if (Dictionary.length[Gap.length].position[i].letter[(int)(ch)-97].words.size < possibiities)
        {
            possibiities = Dictionary.length[Gap.length].position[i].letter[(int)(ch)-97].words.size;
            index = i;
            letter = ch;
            has_constraints = true;
        }
    }

    // then return the words vector with words of a length
    if (has_constraints == false)                       
        return Dictionary.length[Gap.length].words;
    // else return a words vector with a constraint
    return Dictionary.length[Gap.length].position[index].letter[(int)(letter)-97].words;
}

int GetNumberOfSuitableWords(Coordinates Gap, HashTable Dictionary)
{
    Words dictionary = AttachDictionary(Gap, Dictionary);       // get vector of words
    int count = 0;
    bool suitable;

    for (int i = 0; i < dictionary.size; i++)
    {
        suitable = true;
        for (int j = 0; j < Gap.length; j++)
        {
            if (Gap.constraints[j] == ' ')                      // no additional constraint
                continue;
            if (Gap.constraints[j] != dictionary.word[i][j])    // the word is not suitable
                suitable = false;
        }
        if (suitable == true)   // another word that can be placed is found                        
            count++;
    }
    return count;
}

String FindSuitableWord(Coordinates* Gap, HashTable Dictionary)
{
    Words* dictionary = malloc(sizeof(Vector));
    bool suitable;

    // index of last word used from words vector
    // if -1, there is no words vector attached
    if (Gap->index == -1)   
    {
        *dictionary = AttachDictionary(*Gap, Dictionary);
        // get new words vector
        Gap->words_vector = dictionary; 
    }
    else
        dictionary = Gap->words_vector;     // words vector is already set

    for (int i = Gap->index+1; i < dictionary->size; i++)
    {
        suitable = true;

        for (int j = 0; j < Gap->length; j++)
        {
            if (Gap->constraints[j] == ' ')     // no contsraint
                continue;
            if (Gap->constraints[j] != dictionary->word[i][j])  // not suitable
                suitable = false;
        }
        
        if (suitable == true)   // then a word that can be placed is found
        {
            Gap->index = i;
            return dictionary->word[i];
        }
    }
    // then no suitable word is found
    Gap->index = -1;
    return NULL;
}

void PlaceWord(DataGrid* DataGrid, Coordinates* Gap, String Word, int *FLAG)
{
    Gap->filled = true;             // word is placed
    strcpy(Gap->word, Word);
    AddConstraints(DataGrid, *Gap);
    (*FLAG)++;                      // to fill the next gap
}