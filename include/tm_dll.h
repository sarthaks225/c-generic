#ifndef __TM_DLL__H
#define __TM_DLL__H
#include<tm_common.h>

typedef struct __$_tm_dll_node
{
void *ptr;
struct __$_tm_dll_node *next;
struct __$_tm_dll_node *previous;
}DoublyLinkedListNode;

typedef struct __$_tm_dll
{
struct __$_tm_dll_node *start;
struct __$_tm_dll_node *end;
int size;
}DoublyLinkedList;

typedef struct __$_tm_dll_itrator
{
DoublyLinkedListNode *node;
}DoublyLinkedListItrator;


DoublyLinkedList * createDoublyLinkedList(bool *);
void destroyDoublyLinkedList(DoublyLinkedList *);
void clearDoublyLinkedList(DoublyLinkedList *);
void addToDoublyLinkedList(DoublyLinkedList *,void *,bool *);
int getSizeOfDoublyLinkedList(DoublyLinkedList *);

void *getFromDoublyLinkedList(DoublyLinkedList *,int,bool *);
void *removeFromDoublyLinkedList(DoublyLinkedList *,int,bool *);
void insertIntoDoublyLinkedList(DoublyLinkedList *,int,void *,bool *);
void appendToDoublyLinkedList(DoublyLinkedList *,DoublyLinkedList *,bool *);


DoublyLinkedListItrator getDoublyLinkedListItrator(DoublyLinkedList *,bool *);
bool hasNextElementInDoublyLinkedList(DoublyLinkedListItrator *);
void *getNextElementFromDoublyLinkedList(DoublyLinkedListItrator *,bool *);
DoublyLinkedListItrator getDoublyLinkedListItratorFromEnd(DoublyLinkedList *,bool *);
bool hasPreviousElementInDoublyLinkedList(DoublyLinkedListItrator *);
void *getPreviousElementFromDoublyLinkedList(DoublyLinkedListItrator *,bool *);









#endif