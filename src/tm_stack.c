#ifndef __TM_STACK_C
#define __tm_stack_c 121
#include<stdlib.h>
#include<tm_stack.h>


Stack *createStack(bool *success)
{
if(success) *success=false;
Stack *stack;
SinglyLinkedList *singlyLinkedList;

singlyLinkedList=createSinglyLinkedList(success);
if(*success==false) return NULL;

stack=(Stack *)malloc(sizeof(stack));
if(stack==NULL)
{
destroySinglyLinkedList(singlyLinkedList);
if(success) *success=false;
return NULL;
}

stack->singlyLinkedList=singlyLinkedList;
if(success) *success=true;
return stack;
}


void pushOnStack(Stack *stack,void *ptr,bool *success)
{
if(success) *success=false;
if(stack==NULL || stack->singlyLinkedList==NULL) return;
insertIntoSinglyLinkedList(stack->singlyLinkedList,0,ptr,success);
}

void *popFromStack(Stack *stack,bool *success)
{
void *ptr;
if(success) *success=false;
if(isStackEmpty(stack)==true) return NULL;
ptr=removeFromSinglyLinkedList(stack->singlyLinkedList,0,success);
return ptr;
}

int getSizeOfStack(Stack *stack)
{
if(isStackEmpty(stack)==true) return 0;
return getSizeOfSinglyLinkedList(stack->singlyLinkedList);
}

void *getFromTopOfStack(Stack *stack,bool *success)
{
void *ptr;
if(success) *success=false;
if(isStackEmpty(stack)==true) return NULL;
ptr=getFromSinglyLinkedList(stack->singlyLinkedList,0,success);
return ptr;
}

bool isStackEmpty(Stack *stack)
{
if(stack==NULL || stack->singlyLinkedList==NULL) return true;
if(getSizeOfSinglyLinkedList(stack->singlyLinkedList)==0) return true;
return false;
}

void clearStack(Stack *stack)
{
if(stack==NULL || stack->singlyLinkedList==NULL)  return;
clearSinglyLinkedList(stack->singlyLinkedList);
}


void destroyStack(Stack *stack)
{
if(stack==NULL) return;
if(stack->singlyLinkedList==NULL)
{
free(stack);
return;
}
destroySinglyLinkedList(stack->singlyLinkedList);
free(stack);
}

#endif