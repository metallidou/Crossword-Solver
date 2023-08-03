#ifndef SORT_H
#define SORT_H

#include "../grid/GridSTRUCT.h"

// main function to sort DataGrid's information, according to number of word possibilites that can be placed in each gap
// we will first fill the gaps that have fewer word choices 
Grid Sort(Grid Datagrid);

// this function runs using the quick sort algorithm
Coordinates QuickSort(Coordinates Coordinates, int Up, int Down);

// this function swaps data
void Swap(Coordinates Coordinates1, Coordinates Coordinates2);

#endif