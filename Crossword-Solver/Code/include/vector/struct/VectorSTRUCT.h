#pragma once

typedef struct VECTOR Vector;
typedef char* String;

struct VECTOR
{
    String* word;
    int capacity;
    int size;
};

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------