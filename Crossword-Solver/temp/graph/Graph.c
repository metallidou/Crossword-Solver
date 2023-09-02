#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/graph/Graph.h"

Graph GraphInitialize(int Height)
{
    Graph graph;

    graph.height = malloc((Height+1) * sizeof(GraphHeight));

    for (int i = 0; i <= Height; i++)
    {
        graph.height[i].vertex = malloc((26*i) * sizeof(GraphVertex));

        for (int j = 0; j < 26*i; j++)
        {
            graph.height[i].vertex[j].exists = false;
            graph.height[i].vertex[j].level = malloc(i * sizeof(GraphLevel));

            for (int k = 0; k < i; k++)
            {
                for (int l = 0; l < 26; l++)
                    graph.height[i].vertex[j].level[k].vertex[l] = false;
            }
        }
    }
    return graph;
}

void GraphInsert(Graph* Graph, String Word)
{   
    int length = strlen(Word);

    for (int i = 0; i < length; i++)
    {
        Graph->height[length].vertex[26*i+(int)(Word[i])-97].exists = true;

        for (int j = 0; j < length; j++)
        {
            if (i != j)            
                Graph->height[length].vertex[26*i+(int)(Word[i])-97].level[j].vertex[(int)(Word[j])-97] = true;
        }
    }
}

bool GraphPathExists(Graph Graph, String String)
{
    int k, count, hold, length;
    length = strlen(String);
    count = 0;

    for (int i = 0; i < length; i++)
    {
        if (String[i] != ' ')
        {
            if (++count == 1)
                hold = i;
        }        
    }
    
    if (count == 0)
        return true;

    if (count == 1)
    {
        if (Graph.height[length].vertex[hold].exists)
            return true;
        return false;      
    }

    for (int i = 0; i < length; i++)
    {
        if (String[i] != ' ')      
        {
            k = i*26+(int)(String[i])-97;

            if (!Graph.height[length].vertex[k].exists)
                return false;

            for (int j = 0; j < length; j++)
            {
                if ((String[j] != ' ') && (i != j))
                {
                    if (Graph.height[length].vertex[k].level[j].vertex[(int)(String[j])-97] == false)
                        return false;
                }
            }
        }
    }
    return true;
}

String GraphGetPath(Graph Graph, String Visited, String String)
{
    int index, length = strlen(String);
    length = 5;
    char* temp = malloc((length+1) * sizeof(char));
    char letter = ' ';

  //  if (!GraphPathExists(Graph, String))
    //    return NULL;

    length = 5;

    for (int i = 0; i < length; i++)
        temp[i] = ' ';

    if (Visited == NULL)
    {
        for (int i = 0; i < 26; i++)
        {
            if (Graph.height[length].vertex[i].exists == true)
            {
                temp[0] = 97+i;
                break;
            }
        }
    }

    strcpy(temp, "ab s "); 

    for (int i = 0; i < length; i++)
    {
        if (temp[i] != ' ')
            continue;

        for (int j = 0; j < 26; j++)
        {
            for (int k = 0; k < length; k++)
            {
                if (temp[k] == ' ' || k == i)
                    continue;

                if (!Graph.height[length].vertex[k*26+temp[k]-97].level[i].vertex[j])
                {
                    letter = ' ';
                    temp[i] = letter;
                    break;
                }
                else
                {                    
                    letter = 97+j;
                    temp[i] = letter;
                    if (GraphPathExists(Graph, temp))
                    {
                        break;
                    }
                    else
                    {
                        temp[i] = ' ';
                        letter =' ';
                        break;
                    }   
                }
            }
            if (letter != ' ')
            {   
                letter = ' ';
                break;
            }
        }
        
    }
    printf("temp is %s\n", temp);
}
