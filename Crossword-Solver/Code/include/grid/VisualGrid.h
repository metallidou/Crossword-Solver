#pragma once

#include "struct/VisualGridSTRUCT.h"

// read file and get needed information
VisualGrid CreateVisualGrid(char* GridFile);

// width and height of grid
int GetGridDimensions(char* GridFile);

// placement of black boxes 
void GetBlackBoxes(VisualGrid Grid, char* GridFile);

// get coordinates of the words to be placed 
void GetCoordinates(char* String, int *X, int *Y);

// a function that converts text input into an integer
int ReadNumber(char* Text, int *StartIndex, int EndIndex);

// declares whether input is integer 
bool IsInteger(char ch);