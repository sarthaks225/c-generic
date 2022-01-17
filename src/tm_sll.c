#ifndef __TM_SLL_C
#define __tm_sll_c 123
#include<stdlib.h>
#include<tm_sll.h>

SinglyLinkedList * createSinglyLinkedList(bool *success)
{
if(success) *success=false;
SinglyLinkedList *singlyLinkedList;
singlyLinkedList=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
if(singlyLinkedList==NULL) return NULL;
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
singlyLinkedList->size=0;
if(success) *success=true;
return singlyLinkedList;
}

void destroySinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
if(singlyLinkedList==NULL) return;
clearSinglyLinkedList(singlyLinkedList);  
free(singlyLinkedList);
}

int getSizeOfSinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
if(singlyLinkedList==NULL) return 0;
return singlyLinkedList->size;
}

void clearSinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
if(singlyLinkedList==NULL) return;
SinglyLinkedListNode *node;
for(node=singlyLinkedList->start; singlyLinkedList->start!=NULL; node=singlyLinkedList->start)
{
singlyLinkedList->start=node->next;
free(node);
}
singlyLinkedList->end=NULL;
singlyLinkedList->size=0;
}





void addToSinglyLinkedList(SinglyLinkedList *singlyLinkedList,void *ptr,bool *success)
{
SinglyLinkedListNode *node;

if(success) *success=false;
if(singlyLinkedList==NULL) return;
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
if(singlyLinkedList->start==NULL)    //if it is first node
{
singlyLinkedList->start=node;
singlyLinkedList->end=node;
}
else
{
singlyLinkedList->end->next=node;
singlyLinkedList->end=node;
}
singlyLinkedList->size++;
if(success) *success=true;
}

void insertIntoSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,void *ptr,bool *success)
{
if(success) *success=false;
if(singlyLinkedList==NULL) return;
if(index<0 || index>singlyLinkedList->size) return;   //index is smaller then 0 and greater then sll size
SinglyLinkedListNode *node,*p1,*p2;

if(index==singlyLinkedList->size) addToSinglyLinkedList(singlyLinkedList,ptr,success);
else
{
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;

if(index==0)
{
node->next=singlyLinkedList->start;
singlyLinkedList->start=node;
}
else
{
int x=0;
p1=singlyLinkedList->start;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
p2->next=node;
node->next=p1;
}

singlyLinkedList->size++;
}


if(success) *success=true;
}



void * removeFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success)
{
void *ptr;
if(success) *success=false;
SinglyLinkedListNode *p1,*p2;
if(singlyLinkedList==NULL) return NULL;
if(index<0 || index>=singlyLinkedList->size) return NULL;
int x=0;
p1=singlyLinkedList->start;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
ptr=p1->ptr;

if(singlyLinkedList->size==1)
{
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
}
else if(x==0) singlyLinkedList->start=p1->next;
else if(p1==singlyLinkedList->end)
{
singlyLinkedList->end=p2; 
p2->next=NULL;
}
else
{
p2->next=p1->next;
}


free(p1);
singlyLinkedList->size--;
if(success) *success=true;
return ptr;
}



void appendToSinglyLinkedList(SinglyLinkedList *targetSinglyLinkedList,SinglyLinkedList *sourceSinglyLinkedList,bool *success) 
{
bool done;
SinglyLinkedListNode *s,*e,*t,*node;
if(success) *success=false;                 
if(targetSinglyLinkedList==NULL)  return;

if(sourceSinglyLinkedList==NULL || sourceSinglyLinkedList->size==0)
{
if(success) *success=true;
return;
}

done=true;
s=NULL;
e=NULL;
t=sourceSinglyLinkedList->start;
while(t!=NULL)
{
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL)
{
done=false;
break;
}
node->ptr=t->ptr;
node->next=NULL;
if(s==NULL)
{
s=node;
e=node;
}
else
{
e->next=node;
e=node;
}
t=t->next;
}

if(done==false)
{
while(s!=NULL)
{
node=s;
s=s->next;
free(node);
}
return;
}

if(targetSinglyLinkedList->start==NULL)
{
targetSinglyLinkedList->start=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size=sourceSinglyLinkedList->size;
}
else
{

targetSinglyLinkedList->end->next=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size+=sourceSinglyLinkedList->size;
}

if(success) *success=true;
}

void *getFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success)
{

if(success) *success=false;
if(singlyLinkedList==NULL) 
return NULL;
if(index<0 || index>=singlyLinkedList->size) return NULL;

SinglyLinkedListNode *p1;
int x=0;

p1=singlyLinkedList->start;
while(x<index)
{
p1=p1->next;
x++;
}


if(success) *success=true;
return p1->ptr;;
}


SinglyLinkedListItrator getSinglyLinkedListItrator(SinglyLinkedList *singlyLinkedList,bool *success)
{
SinglyLinkedListItrator singlyLinkedListItrator;
singlyLinkedListItrator.node=NULL;
if(success) *success=false;
if(singlyLinkedList==NULL) return singlyLinkedListItrator;

if(success) *success=true;
if(singlyLinkedList->start==NULL) return singlyLinkedListItrator;
else singlyLinkedListItrator.node=singlyLinkedList->start;

return singlyLinkedListItrator;
}

bool hasNextElementInSinglyLinkedList(SinglyLinkedListItrator *singlyLinkedListItrator)
{
if(singlyLinkedListItrator==NULL) return false;
if(singlyLinkedListItrator->node==NULL) return false;
return true;
}

void *getNextElementFromSinglyLinkedList(SinglyLinkedListItrator *singlyLinkedListItrator,bool *success)
{
void *ptr=NULL;

if(success) *success=false;
if(singlyLinkedListItrator==NULL || singlyLinkedListItrator->node==NULL) 
{
return ptr;
}
ptr=singlyLinkedListItrator->node->ptr;
singlyLinkedListItrator->node=singlyLinkedListItrator->node->next;

if(success) *success=true;
return ptr;
}

#endif