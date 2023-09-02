#ifndef VECTOR_H
#define VECTOR_H

#include "VectorSTRUCT.h"
#define MAX_SIZE 20000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/vector/Vector.h"

Vector VectorInitialize();
void VectorInsert(Vector* Vector, String Word);
void VectorRemove(Vector* Vector, String Word);
int VectorEmpty(Vector Vector);

#endif