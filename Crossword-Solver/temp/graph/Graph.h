#ifndef GRAPH_H
#define GRAPH_H

#include "GraphSTRUCT.h"

Graph GraphInitialize(int Height);
void GraphInsert(Graph* Graph, String Word);
bool GraphPathExists(Graph Graph, String String);
String GraphGetPath(Graph Graph, String Visited, String String);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------