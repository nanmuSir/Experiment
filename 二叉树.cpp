#include<stdio.h>

#include<malloc.h>

typedef int ElemType;

typedef struct LNode{

ElemType data;

struct LNode *lchild,*rchild;

}LNode,*TLNode;

void create(TLNode * Tree){  //创建

ElemType e;

scanf("%d",&e);

if(e==0)

*Tree=NULL;

else{

(*Tree)=(TLNode)malloc(sizeof(LNode));

(*Tree)->data=e;

printf("input %d lchild: ",e);

create(&(*Tree)->lchild);


  printf("input %d rchild: ",e);

  create(&(*Tree)->rchild);

}

}

void print1(TLNode Tree){  //先序遍历

if(Tree!=NULL){

printf("%d-",Tree->data);

print1(Tree->lchild);

print1(Tree->rchild);

}

}

void print2(TLNode Tree){  //中序遍历

if(Tree!=NULL){

print2(Tree->lchild);

printf("%d-",Tree->data);

print2(Tree->rchild);

}

}

void print3(TLNode Tree){  //后序遍历

if(Tree!=NULL){

print3(Tree->lchild);

print3(Tree->rchild);

printf("%d-",Tree->data);

}

}

int leaf=0;  //求叶子节点数

int depth(TLNode Tree){  //深度

int s1,s2;

if(Tree==NULL)

return 0;

else{

s1=depth(Tree->lchild);

s2=depth(Tree->rchild);

if(s1==0 && s2==0) leaf++;

return (s1>s2?s1:s2)+1;

}

}

int Cnode(TLNode Tree){  //总结点

int s1,s2;

if(Tree==NULL)

return 0;

else{

s1=Cnode(Tree->lchild);

s2=Cnode(Tree->rchild);

return s1+s2+1;

}

}

int main(){

TLNode Tree;

printf("input 根节点:   ");

create(&Tree);

printf("先序遍历:");

print1(Tree);
printf("\n");
printf("中序遍历");

print2(Tree);
printf("\n"); 
printf("后序遍历");

print3(Tree);
printf("\n");
printf("\n高  度:%d \n",depth(Tree));

printf("总结点数:%d \n",Cnode(Tree));

printf("叶子结点数:%d\n",leaf);
return 0;

}

