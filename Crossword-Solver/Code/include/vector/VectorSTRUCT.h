#ifndef VECTOR_STRUCT_H
#define VECTOR_STRUCT_H

typedef struct VECTOR* Vector;
typedef char* String;

struct VECTOR
{
    String* word;
    int capacity;
    int size;
};

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------