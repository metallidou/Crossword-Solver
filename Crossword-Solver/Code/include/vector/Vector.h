#pragma once

#include "struct/VectorSTRUCT.h"
#define MAX_SIZE 20000

// initialize
Vector VectorInitialize();

// insert
void VectorInsert(Vector* Vector, String Word);

// remove
void VectorRemove(Vector* Vector, String Word);

// is empty
int VectorEmpty(Vector Vector);