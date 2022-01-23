#ifndef __TM_AVLTREE_H
#define __tm_AVLTree_h 121
#include<tm_common.h>
#include<tm_stack.h>
#include<stdio.h>

typedef struct __$_tm_avl_tree_node
{
struct __$_tm_avl_tree_node *left;
struct __$_tm_avl_tree_node *right;
void *ptr;
}AVLTreeNode;

typedef struct __$_tm_avl_tree
{
AVLTreeNode *start;
int (*predicate )(void *,void *);
int size;
}AVLTree;

typedef struct __$_tm_avl_tree_inorder_iterator
{
AVLTreeNode *node;
Stack *stack;
}AVLTreeInOrderIterator;

typedef struct __$_tm_avl_tree_preoder_iterator
{
AVLTreeNode *node;
Stack *stack;
}AVLTreePreOrderIterator;

typedef struct __$_tm_avl_tree_postoder_iterator
{
AVLTreeNode *node;
Stack *stack;
}AVLTreePostOrderIterator;




AVLTree *createAVLTree(bool *,int (*predicate)(void *,void *));
void addToAVLTree(AVLTree *,void *,bool *);
void destroyAVLTree(AVLTree *);
void clearAVLTree(AVLTree *);
     
int getSizeOfAVLTree(AVLTree *);
void *removeFromAVLTree(AVLTree *,void *,bool *);
void *getFromAVLTree(AVLTree *,void *,bool *);


AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *,bool *);
bool hasNextInOrderElementInAVLTree(AVLTreeInOrderIterator *);
void *getNextInOrderElementFromAVLTree(AVLTreeInOrderIterator *,bool *);

AVLTreePreOrderIterator getAVLTreePreOrderIterator(AVLTree *,bool *);
bool hasNextPreOrderElementInAVLTree(AVLTreePreOrderIterator *);
void *getNextPreOrderElementFromAVLTree(AVLTreePreOrderIterator *,bool *);

AVLTreePostOrderIterator getAVLTreePostOrderIterator(AVLTree *,bool *);
bool hasNextPostOrderElementInAVLTree(AVLTreePostOrderIterator *);
void *getNextPostOrderElementFromAVLTree(AVLTreePostOrderIterator *,bool *);


int getHeightOfAVLTree(AVLTreeNode *);


#endif