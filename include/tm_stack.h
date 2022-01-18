#ifndef __TM_STACK__H
#define __TM_STACK__  121
#include<tm_common.h>
#include<tm_sll.h>

typedef struct __$_tm_stack
{
SinglyLinkedList *singlyLinkedList;
}Stack;

Stack *createStack(bool *);
void pushOnStack(Stack *,void *,bool *);
void *popFromStack(Stack *,bool *);
int getSizeOfStack(Stack *);
void *getFromTopOfStack(Stack *,bool *);
bool isStackEmpty(Stack *);
void clearStack(Stack *);
void destroyStack(Stack *);

#endif