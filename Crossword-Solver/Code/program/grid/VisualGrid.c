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

    x = y = GetGridDimensions(GridFile);  
    grid.x = x;         // width
    grid.y = y;         // height

    // memory allocation to store black boxes
    grid.black_box = malloc(x * sizeof(bool*));
    for(i = 0; i < x; i++)
        grid.black_box[i] = malloc(y * sizeof(bool));

    // at first we assume that there are no black boxes
    for(i = 0; i < x; i++)              
    {
        for(j = 0; j < y; j++)
            grid.black_box[i][j] = false;
    }    
    GetBlackBoxes(grid, GridFile);        

    return grid;
}

int GetGridDimensions(char* GridFile)
{
    FILE *file;
    char line[10];
    int start, end, dimensions;

    file = fopen(GridFile, "r");                    // open file
    fgets(line, 10, file);                          // read first line

    start = 0;                                      // number in first line is the dimensions
    end = strlen(line);
    dimensions = ReadNumber(line, &start, end);     // convert string to a number 
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

    *X = ReadNumber(String, &start, end);           // to get coordinate X
    *Y = ReadNumber(String, &start, end);           // to get coordinate Y
}

int ReadNumber(char* Text, int *StartIndex, int EndIndex)
{
    bool get_int = false;
    int integer = 0;    

    for(int i = *StartIndex; i <= EndIndex; i++)
    {
        if((isspace(Text[i]) && get_int == true))       // if an integer is read and we encounter a space, we must return the number      
        {
            *StartIndex = i;
            return integer;
        }
        if (IsInteger(Text[i]))                         // convert to integer
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