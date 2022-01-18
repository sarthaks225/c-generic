#ifndef __TM_QUEUE_C
#define __tm_queue_c 12344
#include<tm_queue.h>
#include<stdlib.h>


Queue *createQueue(bool *success)
{
if(success) *success=false;
Queue *queue;
SinglyLinkedList *singlyLinkedList;

singlyLinkedList=createSinglyLinkedList(success);
if(success==NULL) return NULL;

queue=(Queue *)malloc(sizeof(Queue));
if(queue==NULL)
{
destroySinglyLinkedList(singlyLinkedList);
if(success) *success=false;
return NULL;
}

queue->singlyLinkedList=singlyLinkedList;
if(success) *success=true;
return queue;
}

void addToQueue(Queue *queue,void *ptr,bool *success)
{
if(success) *success=false;
if(queue==NULL || queue->singlyLinkedList==NULL) return;
addToSinglyLinkedList(queue->singlyLinkedList,ptr,success);
}


void *removeFromQueue(Queue *queue,bool *success)
{
void *ptr;
if(success) *success=false;
if(isQueueEmpty(queue)==true) return NULL;
ptr=removeFromSinglyLinkedList(queue->singlyLinkedList,0,success);
return ptr;
}

void *getFromTopOfQueue(Queue *queue,bool *success)
{
void *ptr;
if(success) *success=false;
if(isQueueEmpty(queue)==true) return NULL;
ptr=getFromSinglyLinkedList(queue->singlyLinkedList,0,success);
return ptr;
}


bool isQueueEmpty(Queue *queue)
{
if(queue==NULL || queue->singlyLinkedList==NULL) return true;
if(getSizeOfSinglyLinkedList(queue->singlyLinkedList)==0) return true;
return false;
}

int getSizeOfQueue(Queue *queue)
{
if(isQueueEmpty(queue)==true) return 0;
return getSizeOfSinglyLinkedList(queue->singlyLinkedList);
}

void clearQueue(Queue *queue)
{
if(isQueueEmpty(queue)) return;
clearSinglyLinkedList(queue->singlyLinkedList);
}

void destroyQueue(Queue *queue)
{
if(queue==NULL) return;
if(queue->singlyLinkedList!=NULL) destroySinglyLinkedList(queue->singlyLinkedList);
free(queue);
}

#endif