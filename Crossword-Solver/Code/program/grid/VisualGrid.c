#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../../include/grid/VisualGrid.h"

VisualGrid CreateVisualGrid(char* GridFile)
{
    VisualGrid grid;
    int x, y, i, j;

    // we get grid dimensions
    x = y = GetGridDimensions(GridFile);  // grid is square
    grid.x = x;
    grid.y = y;

    // memory allocation for visual grid
    grid.black_box = malloc(x * sizeof(bool*));
    for(i = 0; i < x; i++)
        grid.black_box[i] = malloc(y * sizeof(bool));

    // at first we assume that all boxes are white
    for(i = 0; i < x; i++)              
    {
        for(j = 0; j < y; j++)
            grid.black_box[i][j] = false;
    }    

    // then we get black boxes
    GetBlackBoxes(grid, GridFile);        

    return grid;
}

int GetGridDimensions(char* GridFile)
{
    FILE *file;
    char line[10];
    int start, end, dimensions;

    // open file and read first line

    file = fopen(GridFile, "r");
    fgets(line, 10, file);

    // get number in first line

    start = 0;
    end = strlen(line);
    dimensions = ReadNumber(line, &start, end);
    fclose(file);

    return dimensions;
}

void GetBlackBoxes(VisualGrid Grid, char* GridFile)
{
    FILE *file = fopen(GridFile, "r");
    char line[100];
    int x, y;

    // we skip first line, because we have already read the dimensions
    fgets(line, 100, file);       

    // get all text file lines, read coordinates and set black boxes
    while(fgets(line, 100, file))
    {   
        GetCoordinates(line, &x, &y);
        Grid.black_box[x-1][y-1] = true;
    }
    fclose(file);
}

void GetCoordinates(char* String, int *X, int *Y)
{
    int start, end;

    start = 0;
    end = strlen(String);

    // to get coordinate X
    *X = ReadNumber(String, &start, end);

    // to get coordinate Y
    *Y = ReadNumber(String, &start, end);
}

int ReadNumber(char* Text, int *StartIndex, int EndIndex)
{
    bool get_int = false;
    int integer = 0;

    for(int i = *StartIndex; i <= EndIndex; i++)
    {
        if((isspace(Text[i]) && get_int == true))      
        {
            *StartIndex = i;
            return integer;
        }
        if (IsInteger(Text[i]))                   // convert to integer
        {
            integer = integer*10 + (Text[i] - '0');
            get_int = true;
        }
    }
    return integer;
}

bool IsInteger(char ch)
{
    return (ch >= '0' && ch <= '9');
}