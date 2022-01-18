#ifndef __TM_QUEUE_H
#define __tm_queue__ 121
#include<tm_common.h>
#include<tm_sll.h>

typedef struct __$_tm_queue
{
SinglyLinkedList *singlyLinkedList;
}Queue;

Queue *createQueue(bool *);
void addToQueue(Queue *,void *,bool *);
void *removeFromQueue(Queue *,bool *);
void *getFromTopOfQueue(Queue *,bool *);
bool isQueueEmpty(Queue *);
int getSizeOfQueue(Queue *);
void clearQueue(Queue *);
void destroyQueue(Queue *);

#endif