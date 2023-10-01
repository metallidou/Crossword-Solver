#pragma once

#include "struct/VectorSTRUCT.h"
#define MAX_SIZE 20000

Vector VectorInitialize();
void VectorInsert(Vector* Vector, String Word);
void VectorRemove(Vector* Vector, String Word);
int VectorEmpty(Vector Vector);
