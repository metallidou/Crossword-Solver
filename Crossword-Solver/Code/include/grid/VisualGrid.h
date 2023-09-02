#ifndef VISUAL_GRID_H
#define VISUAL_GRID_H

#include "VisualGridSTRUCT.h"

VisualGrid CreateVisualGrid(char* GridFile);
int GetGridDimensions(char* GridFile);
void GetBlackBoxes(VisualGrid Grid, char* GridFile);
void GetCoordinates(char* String, int *X, int *Y);
int ReadNumber(char* Text, int *StartIndex, int EndIndex);
bool IsInteger(char ch);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------