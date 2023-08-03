#include <stdbool.h>
#include "GridSTRUCT.h"

// ------------------------------------ DEFINE VISUAL GRID DATA -------------------------------------------------------------------------------------------------

#ifndef GRID_VISUAL_H
#define GRID_VISUAL_H

//---- main function to create grid visualization ----//
GridVisual CreateGridVisualization(char* GridFile);

// this function reads grid dimensions           
int GetGridDimensions(char* GridFile);

// this function reads black boxes
void GetBlackBoxes(GridVisual Grid, char* GridFile);

// this function reads a line from the text file and finds the coordinates x and y
void GetCoordinates(char* String, int *X, int *Y);

// this function takes a part of a string and reads a number contained
int ReadNumber(char* Text, int *StartIndex, int EndIndex);

// this function checks whether a character is integer
bool IsInteger(char ch);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------