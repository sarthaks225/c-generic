#ifndef __TM_AVLTREE_C
#define __tm_avltree_c 123
#include<stdlib.h>
#include<tm_avltree.h>

AVLTree *createAVLTree(bool *success,int (*predicate )(void *,void *))
{
if(success) *success=false;
AVLTree *avlTree;
if(predicate==NULL) return NULL;
avlTree=(AVLTree *)malloc(sizeof(AVLTree));
if(avlTree==NULL) return NULL;
avlTree->start=NULL;
avlTree->predicate=predicate;
avlTree->size=0;
if(success) *success=true;
return avlTree;
}

void addToAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{  
Stack *stack; //stack is for balancing tree
if(success) *success=false;
if(avlTree==NULL || avlTree->predicate==NULL) return;

AVLTreeNode *j,*t;
int weight;
j=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(j==NULL) return;

j->ptr=ptr;
j->left=NULL;
j->right=NULL;

stack=createStack(success); //stack for balancing tree
if(*success==false) 
{
free(j);
return;
}

if(avlTree->start==NULL) avlTree->start=j;
else
{
t=avlTree->start;
while(1)
{

pushOnStack(stack,t,success);
if(*success==false)
{
free(j);
destroyStack(stack);
return;
}

weight=avlTree->predicate(ptr,t->ptr);
if(weight==0)
{
free(j);
destroyStack(stack);
return;
}
if(weight>0) 
{            //insertion at right side of tree
if(t->right==NULL)
{
t->right=j;
break;
}
t=t->right;
}
else
{      //insertion at left side of tree
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
balanceAVLTree(avlTree,stack);
destroyStack(stack);
if(success) *success=true;
}

void destroyAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return;
clearAVLTree(avlTree);
free(avlTree);
}

int getSizeOfAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return 0;
return avlTree->size;
}

void clearAVLTree(AVLTree *avlTree)
{
bool success;
if(avlTree==NULL || avlTree->start==NULL) return;
AVLTreeNode *node; 
Queue *queue;
queue=createQueue(&success);
if(success==false) return;
AVLTreePostOrderIterator itr;

itr=getAVLTreePostOrderIterator(avlTree,&success);
if(success==false) return;
while(hasNextPostOrderElementInAVLTree(&itr))
{
addToQueue(queue,getNextPostOrderElementFromAVLTree(&itr,&success),&success);
if(success==false)
{
destroyQueue(queue);
return;
}
}

while(isQueueEmpty(queue))
{
node=removeFromQueue(queue,&success);
free(node);
}
avlTree->start=NULL;
avlTree->size=0;
}
     
void *removeFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
Stack *stack;
if(success) *success=false;
if(avlTree==NULL || avlTree->start==NULL || avlTree->predicate==NULL) return NULL;
int weight;
AVLTreeNode *t,*j,*e,*f,**p2p;
void *foundPtr;

stack=createStack(success);
if(*success==false) return NULL;

for(t=avlTree->start; t!=NULL; )
{         //searching ptr in tree

weight=avlTree->predicate(ptr,t->ptr);
if(weight==0) break;
j=t;
pushOnStack(stack,t,success); //push on stack for balancing
if(*success==false)
{
destroyStack(stack); return NULL;
}
if(weight>0) t=t->right; else t=t->left;
}

if(t==NULL)  //if ptr not found
{
destroyStack(stack);
return NULL;
}
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
balanceAVLTree(avlTree,stack);
destroyStack(stack);
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

int getHeightOfAVLTree(AVLTreeNode *node)
{
if(node==NULL) return 0;
int leftHeight,rightHeight;
leftHeight=getHeightOfAVLTree(node->left);
rightHeight=getHeightOfAVLTree(node->right);
return (leftHeight>rightHeight)?leftHeight+1:rightHeight+1;
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
if(*success==false) return avlTreeInOrderIterator;

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

bool hasNextInOrderElementInAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator)
{
if(avlTreeInOrderIterator==NULL || avlTreeInOrderIterator->node==NULL) return false;
return true;
}


void *getNextInOrderElementFromAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator,bool *success)
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

//............  AVLTreePreOrderIterator......

AVLTreePreOrderIterator getAVLTreePreOrderIterator(AVLTree *avlTree,bool *success)
{
if(success) *success=false;
AVLTreePreOrderIterator avlTreePreOrderIterator;
AVLTreeNode *node;

avlTreePreOrderIterator.node=NULL;
avlTreePreOrderIterator.stack=NULL;

if(avlTree==NULL) return avlTreePreOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreePreOrderIterator;
}

avlTreePreOrderIterator.stack=createStack(success);
if(*success==false) return avlTreePreOrderIterator;

node=avlTree->start;

avlTreePreOrderIterator.node=node;
if(success) *success=true;
return avlTreePreOrderIterator;
}

bool hasNextPreOrderElementInAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator)
{
if(avlTreePreOrderIterator==NULL || avlTreePreOrderIterator->node==NULL) return false;
return true;
}


void *getNextPreOrderElementFromAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator,bool *success)
{
if(success) *success=false;

if(avlTreePreOrderIterator==NULL || avlTreePreOrderIterator->node==NULL) return NULL;
AVLTreeNode *node,*j;

j=avlTreePreOrderIterator->node;

node=j->right;
if(node!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,node,success);
if(*success==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}

}

node=j->left;
if(node!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,node,success);
if(*success==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}

}

if(isStackEmpty(avlTreePreOrderIterator->stack))
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
}
else
{
avlTreePreOrderIterator->node=(AVLTreeNode *)popFromStack(avlTreePreOrderIterator->stack,success);
}

if(success) *success=true;
return j->ptr;
}

//...........................................
//...........AVLTreePostOrderIterator
AVLTreePostOrderIterator getAVLTreePostOrderIterator(AVLTree *avlTree,bool *success)
{
if(success) *success=false;
AVLTreePostOrderIterator avlTreePostOrderIterator;
avlTreePostOrderIterator.node=NULL;
avlTreePostOrderIterator.stack=NULL;

if(avlTree==NULL) return avlTreePostOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreePostOrderIterator;
}

AVLTreeNode *node;
avlTreePostOrderIterator.stack=createStack(success);
if(*success==false) return avlTreePostOrderIterator;

node=avlTree->start;

while(1)
{

while(node!=NULL)
{

if(node->right!=NULL)
{
pushOnStack(avlTreePostOrderIterator.stack,node->right,success);
if(*success==false)
{
destroyStack(avlTreePostOrderIterator.stack);
avlTreePostOrderIterator.node=NULL;
avlTreePostOrderIterator.stack=NULL;
return avlTreePostOrderIterator;
}
}

pushOnStack(avlTreePostOrderIterator.stack,node,success);
if(*success==false)
{
destroyStack(avlTreePostOrderIterator.stack);
avlTreePostOrderIterator.node=NULL;
avlTreePostOrderIterator.stack=NULL;
return avlTreePostOrderIterator;
}
node=node->left;
}

node=popFromStack(avlTreePostOrderIterator.stack,success);
if(isStackEmpty(avlTreePostOrderIterator.stack))
{
destroyStack(avlTreePostOrderIterator.stack);
avlTreePostOrderIterator.stack=NULL;
break;
}

if(!isStackEmpty(avlTreePostOrderIterator.stack) && node->right!=NULL && node->right==getFromTopOfStack(avlTreePostOrderIterator.stack,success))
{
popFromStack(avlTreePostOrderIterator.stack,success);
pushOnStack(avlTreePostOrderIterator.stack,node,success);
if(*success==false)
{
destroyStack(avlTreePostOrderIterator.stack);
avlTreePostOrderIterator.node=NULL;
avlTreePostOrderIterator.stack=NULL;
return  avlTreePostOrderIterator;
}
node=node->right;
}
else
{
break;
}

}

avlTreePostOrderIterator.node=node;
if(success) *success=true;
return  avlTreePostOrderIterator;
}

bool hasNextPostOrderElementInAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator)
{
if(avlTreePostOrderIterator==NULL || avlTreePostOrderIterator->node==NULL) return false;
return true;
}

void *getNextPostOrderElementFromAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator,bool *success)
{
if(success) *success=false;
if(!hasNextPostOrderElementInAVLTree(avlTreePostOrderIterator)) return NULL;

AVLTreeNode *node,*j;
j=avlTreePostOrderIterator->node;

if(isStackEmpty(avlTreePostOrderIterator->stack))
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->stack=NULL;
avlTreePostOrderIterator->node=NULL;
}
else
{

node=NULL;
while(1)
{

while(node!=NULL)
{
if(node->right!=NULL)
{
pushOnStack(avlTreePostOrderIterator->stack,node->right,success);
if(*success==false)
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->stack=NULL;
avlTreePostOrderIterator->node=NULL;
break;
}
}

pushOnStack(avlTreePostOrderIterator->stack,node,success);
if(*success==false)
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->stack=NULL;
avlTreePostOrderIterator->node=NULL;
break;
}

node=node->left;
}

node=popFromStack(avlTreePostOrderIterator->stack,success);

if(!isStackEmpty(avlTreePostOrderIterator->stack) && node->right!=NULL && node->right==getFromTopOfStack(avlTreePostOrderIterator->stack,success))
{
popFromStack(avlTreePostOrderIterator->stack,success);
pushOnStack(avlTreePostOrderIterator->stack,node,success);
if(*success==false)
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->stack=NULL;
avlTreePostOrderIterator->node=NULL;
break;
}

node=node->right;
}
else
{
avlTreePostOrderIterator->node=node;
break;
}

}

}

if(success) *success=true;
return j->ptr;
}

//........................

void balanceAVLTree(AVLTree *avlTree,Stack *stack)
{
if(isStackEmpty(stack)) return;

bool success;
AVLTreeNode *root,*parent,*lc,*rc,*lcrc,*rclc,**p2p;
int diff,lh,rh;

while(!isStackEmpty(stack))
{

root=popFromStack(stack,&success);
rc=root->right;
lc=root->left;
lh=getHeightOfAVLTree(lc);
rh=getHeightOfAVLTree(rc);
diff=lh-rh;
if(diff>=-1 && diff<=1) continue;
parent=getFromTopOfStack(stack,&success);

if(isStackEmpty(stack)) p2p=&(avlTree->start);
else
{
if(parent->left==root) p2p=&(parent->left);
else p2p=&(parent->right);
}

if(rh>lh)  //balance rh
{
rclc=rc->left;
if(getHeightOfAVLTree(rclc)>getHeightOfAVLTree(rc->right))
{
rc->left=rclc->right;         // right is left heavy
rclc->right=rc;
root->right=rclc;
}
                             //now 100%right is right heavy

rc=root->right;
root->right=rc->left;
rc->left=root;
*p2p=rc;
}
else  //balance lh
{
lcrc=lc->right;
if(getHeightOfAVLTree(lcrc)>getHeightOfAVLTree(lc->left))
{
lc->right=lcrc->left;       //left is right heavy
lcrc->left=lc;
root->left=lcrc;
}
                           //now 100% left is left heavy

lc=root->left;
root->left=lc->right;
lc->right=root;
*p2p=lc;
}

}

}


#endif