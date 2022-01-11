#ifndef __TM_SLL__H
#define __TM_SLL__ 1234
#include<tm_common.h>
typedef struct __$_tm_sll_node
{
void *ptr;
struct __$_tm_sll_node *next;
}SinglyLinkedListNode;

typedef struct __$_tm_sll
{
struct __$_tm_sll_node *start;
struct __$_tm_sll_node *end;
int size;
}SinglyLinkedList;

typedef struct __$_tm_sll_itrator
{
SinglyLinkedListNode *node;
}SinglyLinkedListItrator;


SinglyLinkedList * createSinglyLinkedList(bool *);
void destroySinglyLinkedList(SinglyLinkedList *);
void clearSinglyLinkedList(SinglyLinkedList *);
int getSizeOfSinglyLinkedList(SinglyLinkedList *);

void addToSinglyLinkedList(SinglyLinkedList *,void *,bool *);
void insertIntoSinglyLinkedList(SinglyLinkedList *,int,void *,bool *);
void * removeFromSinglyLinkedList(SinglyLinkedList *,int,bool *);

void appendToSinglyLinkedList(SinglyLinkedList *,SinglyLinkedList *,bool *);
void *getFromSinglyLinkedList(SinglyLinkedList *,int index,bool *);

SinglyLinkedListItrator getSinglyLinkedListItrator(SinglyLinkedList *,bool *);
bool hasNextElementInSinglyLinkedList(SinglyLinkedListItrator *);
void *getNextElementFromSinglyLinkedList(SinglyLinkedListItrator *,bool *);


#endif