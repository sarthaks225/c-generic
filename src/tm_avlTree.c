#ifndef __TM_AVLTREE_C
#define __tm_avltree_c 123
#include<stdlib.h>
#include<tm_avltree.h>

AVLTree *createAVLTree(bool *success,int (*predicate )(void *,void *))
{
if(success) *success=false;
AVLTree *avlTree;
avlTree=(AVLTree *)malloc(sizeof(AVLTree));
if(avlTree==NULL || predicate==NULL) return NULL;
avlTree->start=NULL;
avlTree->predicate=predicate;
avlTree->size=0;
if(success) *success=true;
return avlTree;
}

void addToAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{  

if(success) *success=false;
if(avlTree==NULL || avlTree->predicate==NULL) return;

AVLTreeNode *j,*t;
int weight;
j=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(j==NULL) return;

j->ptr=ptr;
j->left=NULL;
j->right=NULL;

if(avlTree->start==NULL) avlTree->start=j;
else
{

t=avlTree->start;
while(1)
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0)
{
free(j);
return;
}
if(weight>0) 
{
                 //insertion at right side of tree
if(t->right==NULL) 
{
t->right=j;
break;
}
t=t->right;
}
else
{
                //insertion at left side of tree
if(t->left==NULL)
{
t->left=j;
break;
}
t=t->left;
}

}

}


avlTree->size++;
if(success) *success=true;
}


void destroyAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return;
clearAVLTree(avlTree);
}

int getSizeOfAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return 0;
return avlTree->size;
}

void clearAVLTree(AVLTree *avlTree)
{

}
     
void *removeFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
if(success) *success=false;
if(avlTree==NULL || avlTree->start==NULL || avlTree->predicate==NULL) return NULL;
int weight;
AVLTreeNode *t,*j,*e,*f,**p2p;
void *foundPtr;

for(t=avlTree->start; t!=NULL; )
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0) break;
j=t;
if(weight>0) t=t->right; else t=t->left;
}
if(t==NULL) return NULL;
foundPtr=t->ptr;

if(t==avlTree->start) p2p=&(avlTree->start);
else if(j->left==t) p2p=&(j->left);
else p2p=&(j->right);

if(t->left==t->right) //ptr is leaf node
{
*p2p=NULL;
}
else
{

if(t->right!=NULL) 
{
for(e=t->right; e->left!=NULL; e=e->left) f=e;

if(e==t->right)
{
e->left=t->left;
}
else
{
f->left=e->right;
e->left=t->left;
e->right=t->right;
}
*p2p=e;

}  //successor part ends
else
{  //searching for predecesor

for(e=t->left; e->right!=NULL; e=e->right) f=e;

if(e!=t->left)
{
f->right=e->left;
e->left=t->left;
}
*p2p=e;

}

}


free(t);
if(success) *success=true;
avlTree->size--;
return foundPtr;
}

void *getFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
if(success) *success=false;
if(avlTree==NULL|| avlTree->start==NULL || avlTree->predicate==NULL) return NULL;
AVLTreeNode *node;
int weight;
node=avlTree->start;

while(node!=NULL)
{
weight=avlTree->predicate(ptr,node->ptr);
if(weight==0)
{
if(success) *success=true;
return node->ptr;
}
if(weight>0) node=node->right;
else node=node->left;
}

return NULL;
}





//.......................  AVLTreeInOrderIterator ......................................
AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *avlTree,bool *success)
{
if(success) *success=false;
AVLTreeInOrderIterator avlTreeInOrderIterator;
AVLTreeNode *node;

avlTreeInOrderIterator.node=NULL;
avlTreeInOrderIterator.stack=NULL;

if(avlTree==NULL) return avlTreeInOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreeInOrderIterator;
}

avlTreeInOrderIterator.stack=createStack(success);
if(success==false) return avlTreeInOrderIterator;

node=avlTree->start;
while(node!=NULL)
{
pushOnStack(avlTreeInOrderIterator.stack,node,success);
if(*success==false)
{
destroyStack(avlTreeInOrderIterator.stack);
avlTreeInOrderIterator.stack=NULL;
return avlTreeInOrderIterator;
}
node=node->left;
}

avlTreeInOrderIterator.node=popFromStack(avlTreeInOrderIterator.stack,success);
return avlTreeInOrderIterator;
}

bool hasNextElementInAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator)
{
if(avlTreeInOrderIterator==NULL || avlTreeInOrderIterator->node==NULL) return false;
return true;
}


void *getNextElementFromAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator,bool *success)
{
if(success) *success=false;

if(avlTreeInOrderIterator==NULL || avlTreeInOrderIterator->node==NULL) return NULL;
AVLTreeNode *node,*j;

j=avlTreeInOrderIterator->node;
node=j->right;
while(node!=NULL)
{
pushOnStack(avlTreeInOrderIterator->stack,node,success);
if(*success==false)
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->stack=NULL;
avlTreeInOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}
node=node->left;
}

if(isStackEmpty(avlTreeInOrderIterator->stack))
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->stack=NULL;
avlTreeInOrderIterator->node=NULL;
}
else
{
avlTreeInOrderIterator->node=(AVLTreeNode *)popFromStack(avlTreeInOrderIterator->stack,success);
}

if(success) *success=true;
return j->ptr;
}
//...................................................................

#endif