#ifndef __TM_DLL_C
#define __tm_dll_c
#include<stdlib.h>
#include<tm_dll.h>

DoublyLinkedList * createDoublyLinkedList(bool *success)
{
DoublyLinkedList *doublyLinkedList;

if(success) *success=false;
doublyLinkedList=(DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
if(doublyLinkedList==NULL) return doublyLinkedList;
doublyLinkedList->start=NULL;
doublyLinkedList->end=NULL;
doublyLinkedList->size=0;

if(success) *success=true;
return doublyLinkedList;
}

void destroyDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
DoublyLinkedListNode *node;

if(doublyLinkedList==NULL) return;
clearDoublyLinkedList(doublyLinkedList);
free(doublyLinkedList);
}

void clearDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
DoublyLinkedListNode *node;
if(doublyLinkedList==NULL) return;
for(node=doublyLinkedList->start; doublyLinkedList->start!=NULL; node=doublyLinkedList->start)
{
doublyLinkedList->start=node->next;
free(node);
}
doublyLinkedList->end=NULL;
doublyLinkedList->size=0;
}

void addToDoublyLinkedList(DoublyLinkedList *doublyLinkedList,void *ptr,bool *success)
{
DoublyLinkedListNode *node;
if(success)  *success=false;
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL) return;
node->next=NULL;
node->previous=NULL;
node->ptr=ptr;
if(doublyLinkedList->start==NULL)  //adding first node list
{
doublyLinkedList->start=node;
doublyLinkedList->end=node;
}
else                              //adingNode at end in list 
{
node->previous=doublyLinkedList->end;
doublyLinkedList->end->next=node;
doublyLinkedList->end=node;
}

doublyLinkedList->size++;
if(success) *success=true;
}

int getSizeOfDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
if(doublyLinkedList==NULL) return 0;
return  doublyLinkedList->size;
}

void *getFromDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,bool *success)
{
if(success) *success=false;

if(doublyLinkedList==NULL || doublyLinkedList->start==NULL) return NULL;
if(index<0 || index>=doublyLinkedList->size) return NULL;

DoublyLinkedListNode *node;
node=doublyLinkedList->start;
int j=0;

while(j<index)
{
node=node->next;
j++;
}

if(success) *success=true;
return node->ptr;
}

void * removeFromDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,bool *success)
{
DoublyLinkedListNode *p1,*p2;
void *ptr;
if(success) *success=false;
if(doublyLinkedList==NULL || doublyLinkedList->start==NULL) return NULL;
if(index<0 || index>=doublyLinkedList->size) return NULL;

int j;
p1=doublyLinkedList->start;
for(j=0; j<index; j++)
{
p2=p1;
p1=p1->next;
}
ptr=p2->ptr;
if(doublyLinkedList->size==1)
{
doublyLinkedList->start=NULL;
doublyLinkedList->end=NULL;
}
else if(j==0) doublyLinkedList->start=p1->next;
else if(doublyLinkedList->end==p1) doublyLinkedList->end=p2;
else
{
p2->next=p1->next;
p1->next->previous=p2;
}

free(p1);
if(success) *success=true;
doublyLinkedList->size--;
return ptr;
}



void insertIntoDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,void *ptr,bool *success)
{

if(success) *success=false;
if(doublyLinkedList==NULL) return;
if(index<0 || index>doublyLinkedList->size) return;

if(index==doublyLinkedList->size) addToDoublyLinkedList(doublyLinkedList,ptr,success);
else
{
DoublyLinkedListNode *node,*p1,*p2;

node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
node->previous=NULL;

int x=0;
p1=doublyLinkedList->start;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}

if(x==0)
{
node->next=p1;
p1->previous=node;
doublyLinkedList->start=node;
}
else
{
p2->next=node;
node->next=p1;
node->previous=p2;
p1->previous=node;
}

doublyLinkedList->size++;
}

if(success) *success=true;
}



void appendToDoublyLinkedList(DoublyLinkedList *targetDoublyLinkedList,DoublyLinkedList *sourceDoublyLinkedList,bool *success)
{    
if(success) *success=false;
if(targetDoublyLinkedList==NULL) return;
if(sourceDoublyLinkedList==NULL || sourceDoublyLinkedList->size==0)
{
if(success) *success=true;
return;
}

DoublyLinkedListNode *t,*node,*s,*e;
bool done;
done=true;
s=e=node=NULL;


for(t=sourceDoublyLinkedList->start; t!=NULL; t=t->next)
{
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL)
{
done=false;
break;
}
node->ptr=t->ptr;
node->next=NULL;
node->previous=NULL;
if(s==NULL)
{
s=node;
e=node;
}
else
{
e->next=node;
node->previous=e;
e=node;
}

}


if(done==false)
{

for(node=s; s!=NULL; node=s)
{
s=s->next;
free(node);
}
return;
}


if(targetDoublyLinkedList->start==NULL)
{
targetDoublyLinkedList->start=s;
targetDoublyLinkedList->end=e;
targetDoublyLinkedList->size=sourceDoublyLinkedList->size;
}
else
{
s->previous=targetDoublyLinkedList->end;
targetDoublyLinkedList->end->next=s;
targetDoublyLinkedList->end=e;
targetDoublyLinkedList->size+=sourceDoublyLinkedList->size;
}

if(success) *success=true;
}

DoublyLinkedListItrator getDoublyLinkedListItrator(DoublyLinkedList *doublyLinkedList,bool *success)
{
if(success) *success=false;
DoublyLinkedListItrator doublyLinkedListItrator;
doublyLinkedListItrator.node=NULL;
if(doublyLinkedList==NULL) return doublyLinkedListItrator;
if(doublyLinkedList->start==NULL)
{
if(success) *success=true;
return doublyLinkedListItrator;
}

doublyLinkedListItrator.node=doublyLinkedList->start;
if(success) *success=true;
return doublyLinkedListItrator;
}

bool hasNextElementInDoublyLinkedList(DoublyLinkedListItrator *doublyLinkedListItrator)
{
if(doublyLinkedListItrator==NULL || doublyLinkedListItrator->node==NULL)  return false;
return true;
}

void *getNextElementFromDoublyLinkedList(DoublyLinkedListItrator *doublyLinkedListItrator,bool *success)
{
void *ptr=NULL;
if(success) *success=false;
if(doublyLinkedListItrator==NULL || doublyLinkedListItrator->node==NULL) return ptr;
ptr=doublyLinkedListItrator->node->ptr;
doublyLinkedListItrator->node=doublyLinkedListItrator->node->next;
if(success) *success=true;
return ptr;
}

DoublyLinkedListItrator getDoublyLinkedListItratorFromEnd(DoublyLinkedList *doublyLinkedList,bool *success)
{
DoublyLinkedListItrator doublyLinkedListItrator;
doublyLinkedListItrator.node=NULL;
if(success) *success=false;
if(doublyLinkedList==NULL) return doublyLinkedListItrator;

if(doublyLinkedList->end==NULL)
{
if(success) *success=true;
return doublyLinkedListItrator;
}

doublyLinkedListItrator.node=doublyLinkedList->end;
if(success) *success=true;
return doublyLinkedListItrator;
}

bool hasPreviousElementInDoublyLinkedList(DoublyLinkedListItrator *doublyLinkedListItrator)
{
if(doublyLinkedListItrator==NULL || doublyLinkedListItrator->node==NULL) return false;
return true;
}

void *getPreviousElementFromDoublyLinkedList(DoublyLinkedListItrator *doublyLinkedListItrator,bool *success)
{
void *ptr;
ptr=NULL;
if(success) *success=false;
if(doublyLinkedListItrator==NULL || doublyLinkedListItrator->node==NULL) return ptr;
ptr=doublyLinkedListItrator->node->ptr;
doublyLinkedListItrator->node=doublyLinkedListItrator->node->previous;
if(success) *success=true;
return ptr;
}


#endif