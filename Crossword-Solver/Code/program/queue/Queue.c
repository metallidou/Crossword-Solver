#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/queue/Queue.h"

Queue QueueInitialize(Queue Queue)
{
   Queue = malloc(sizeof(struct QUEUE));
   Queue->front = NULL;
   Queue->rear = NULL;
   return Queue;
}

int QueueEmpty(Queue Queue)
{
   return (Queue->front == NULL);
}

Queue QueueInsert(char* Word, Queue Queue)
{
    QueueNode temp = malloc(sizeof(struct WordsQUEUE));
    temp->word = malloc((strlen(Word)+1) * sizeof(char));
    
    strcpy(temp->word, Word);
    temp->next = NULL;

    if(QueueEmpty(Queue))
    {
        Queue->front = temp;
        Queue->rear = temp;
    } 
    else 
    {
        Queue->rear->next = temp;
        Queue->rear = temp;
    }
    return Queue;
}

Queue QueueRemove(Queue Queue, char* Word)
{
   QueueNode temp;

    if(!QueueEmpty(Queue))
    {
        strcpy(Word, Queue->front->word);  
        temp = Queue->front;
        Queue->front = temp->next;
    
        free(temp->word);
        free(temp);

        if(Queue->front == NULL) 
            Queue->rear = NULL;     
    }   
    return Queue;
}