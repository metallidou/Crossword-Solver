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
    grid.x = x;         
    grid.y = y;         

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
    int dimensions;

    file = fopen(GridFile, "r");                    
    
    // number in first line is the dimensions
    fscanf(file, "%d", &dimensions);
    
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
    while (fscanf(file, "%d %d", &x, &y) == 2) 
        Grid.black_box[x - 1][y - 1] = true;
    
    fclose(file);
}

void FreeVisualGrid(VisualGrid* VisualGrid)
{
    for (int i = 0; i < VisualGrid->x; i++)
        free(VisualGrid->black_box[i]);
    free(VisualGrid->black_box);    
}