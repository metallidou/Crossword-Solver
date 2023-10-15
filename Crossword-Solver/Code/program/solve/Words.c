#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "../../include/solve/Words.h"

bool IsWordAcceptable(DataGrid DataGrid, Coordinates Gap, HashTable HashTable)
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
                if (!FindSuitableWord(&(DataGrid.vertically->gap[index]), HashTable))
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
                if (!FindSuitableWord(&(DataGrid.horizontally->gap[index]), HashTable))
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

Words* AttachHashTable(Coordinates Gap, HashTable HashTable)
{
    int index, possibiities = INT_MAX;
    bool has_constraints = false;
    char letter, ch;

    for (int i = 0; i < Gap.length; i++)
    {
        // ch represents a constrained letter 
        ch = Gap.constraints[i];
        
        // free letter
        if (ch == ' ')  
            continue;
        
        // we try to find the best possible vector with constrained words, in terms of possibilities
        // the HashTable offers a vector of words with only one constraint at the time
        if (HashTable.length[Gap.length].position[i].letter[(int)(ch)-97].words.size < possibiities)
        {
            possibiities = HashTable.length[Gap.length].position[i].letter[(int)(ch)-97].words.size;
            index = i;
            letter = ch;
            has_constraints = true;
        }
    }

    // then return the words vector with words of a length
    if (has_constraints == false)                       
        return &(HashTable.length[Gap.length].words);
    // else return a words vector with a constraint
    return &(HashTable.length[Gap.length].position[index].letter[(int)(letter)-97].words);
}

int GetNumberOfSuitableWords(Coordinates Gap, HashTable HashTable)
{
    // get vector of words
    Words* dictionary = AttachHashTable(Gap, HashTable);       
    bool suitable;
    int count = 0;

    for (int i = 0; i < dictionary->size; i++)
    {
        suitable = true;
        for (int j = 0; j < Gap.length; j++)
        {
            // no additional constraint
            if (Gap.constraints[j] == ' ')                      
                continue;
            if (Gap.constraints[j] != dictionary->word[i][j])    
                suitable = false;
        }
        // another word that can be placed is found       
        if (suitable == true)                    
            count++;
    }
    return count;
}

String FindSuitableWord(Coordinates* Gap, HashTable HashTable)
{
    bool suitable;

    // index of last word used from words vector
    // if -1, there is no words vector attached
    if (Gap->index == -1)   
        Gap->words_vector = AttachHashTable(*Gap, HashTable);

    for (int i = Gap->index+1; i < Gap->words_vector->size; i++)
    {
        suitable = true;

        for (int j = 0; j < Gap->length; j++)
        {
            // no constraint
            if (Gap->constraints[j] == ' ')     
                continue;
            if (Gap->constraints[j] != Gap->words_vector->word[i][j])  
                suitable = false;
        }
        // then a word that can be placed is found
        if (suitable == true)   
        {
            Gap->index = i;
            return Gap->words_vector->word[i];
        }
    }
    // then no suitable word is found
    Gap->index = -1;
    return NULL;
}

void PlaceWord(DataGrid* DataGrid, Coordinates* Gap, String Word, int *FLAG)
{
    // word is placed
    Gap->filled = true;             
    strcpy(Gap->word, Word);

    AddConstraints(DataGrid, *Gap);
    // to fill the next gap
    (*FLAG)++;                      
}