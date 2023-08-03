#ifndef VECTOR_H
#define VECTOR_H

#include "VectorSTRUCT.h"
#define MAX_SIZE 20000

Vector VectorInitialize(Vector Vector);
Vector VectorInsert(Vector Vector, String Word);
Vector VectorRemove(Vector Vector, String Word);
int VectorEmpty(Vector Vector);

#endif