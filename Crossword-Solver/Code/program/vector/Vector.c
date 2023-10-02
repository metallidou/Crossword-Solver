#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/vector/Vector.h"

Vector VectorInitialize()
{
    Vector vector;

    vector.capacity = MAX_SIZE;
    vector.size = 0;
    vector.word = malloc(vector.capacity * sizeof(String));
    return vector;
}

void VectorInsert(Vector* Vector, String Word)
{
    int size, capacity;
    size = Vector->size; 
    capacity = Vector->capacity;

    if(size < capacity)         // another word can be added
    {
        Vector->word[size] = malloc((strlen(Word)+1) * sizeof(char));
        strcpy(Vector->word[size], Word);
        Vector->size++;
    }
}

void VectorRemove(Vector* Vector, String Word)
{
    if(!VectorEmpty(*Vector))
    {
        strcpy(Word, Vector->word[Vector->size-1]);
        free(Vector->word[Vector->size-1]);
        Vector->size--;
    }
}

int VectorEmpty(Vector Vector)
{
    return (Vector.size == 0);
}

void FreeVector(Vector* Vector)
{
    for (int i = 0; i < Vector->size; i++)
        free(Vector->word[i]);
    free(Vector->word);
}