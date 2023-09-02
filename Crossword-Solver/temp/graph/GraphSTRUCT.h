#ifndef GRAPH_STRUCT_H
#define GRAPH_STRUCT_H

#include <stdbool.h>

typedef char* String;

typedef struct GraphSTRUCT Graph;
typedef struct GraphHeightSTRUCT GraphHeight;
typedef struct GraphVertexSTRUCT GraphVertex;
typedef struct GraphLevelSTRUCT GraphLevel;

struct GraphSTRUCT
{
    GraphHeight* height;
};

struct GraphHeightSTRUCT
{
    GraphVertex* vertex;
};

struct GraphVertexSTRUCT
{
    bool exists;
    GraphLevel* level;
};

struct GraphLevelSTRUCT
{
    bool vertex[26];
};

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------