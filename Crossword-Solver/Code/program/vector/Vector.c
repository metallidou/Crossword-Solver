#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/vector/Vector.h"

Vector VectorInitialize(Vector Vector)
{
    Vector->capacity = MAX_SIZE;
    Vector->size = 0;
    Vector->word = malloc(Vector->capacity * sizeof(String));
    return Vector;
}

Vector VectorInsert(Vector Vector, String Word)
{
    int size, capacity;
    size = Vector->size; 
    capacity = Vector->capacity;

    if(size < capacity)
    {
        Vector->word[size] = malloc((strlen(Word)+1) * sizeof(char));
        strcpy(Vector->word[size], Word);
        Vector->size++;
    }
    return Vector;
}

Vector VectorRemove(Vector Vector, String Word)
{
    if(!VectorEmpty(Vector))
    {
        strcpy(Word, Vector->word[Vector->size-1]);
        free(Vector->word[Vector->size-1]);
        Vector->size--;
    }
    return Vector;
}

int VectorEmpty(Vector Vector)
{
    return (Vector->size == 0);
}