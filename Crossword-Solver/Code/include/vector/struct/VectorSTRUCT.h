#pragma once

typedef struct VECTOR Vector;
typedef char* String;

struct VECTOR               // this struct holds vectors of strings
{
    String* word;           // array of words
    int capacity;           // number of words it can hold
    int size;               // current size of vector
};