#ifndef QUEUE_H
#define QUEUE_H

#include "QueueSTRUCT.h"

// this function initializes a queue
Queue QueueInitialize(Queue Queue);

// this functions indicates whether a queue is empty or not
int QueueEmpty(Queue Queue);

// this function inserts a new element to queue
Queue QueueInsert(char* Word, Queue Queue);

// this function removes a queue's first element and returns it
Queue QueueRemove(Queue Queue, char* Word);

#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------