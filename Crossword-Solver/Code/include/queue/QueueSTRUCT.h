#ifndef QUEUE_STRUCT_H
#define QUEUE_STRUCT_H

typedef struct QUEUE* Queue;
typedef struct WordsQUEUE* QueueNode; 

struct QUEUE 
{
    QueueNode front;
    QueueNode rear;
};

struct WordsQUEUE 
{
    char* word;
    QueueNode next;
};

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------