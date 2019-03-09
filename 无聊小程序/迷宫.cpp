#include<iostream>  
#include <malloc.h>
using namespace std;  
struct PosType /* 迷宫坐标位置类型 */  
 {  
   int x; /* 行值 */  
   int y; /* 列值 */  
 };  
#define MAXLENGTH 25 /* 设迷宫的最大行列为25 */  
 typedef int MazeType[MAXLENGTH][MAXLENGTH]; /* 迷宫数组[行][列] */  
 /* 全局变量 */  
 MazeType m; /* 迷宫数组 */  
 int curstep=1; /* 当前足迹,初值为1 */  
 int a[MAXLENGTH];  
 int b[MAXLENGTH];  
 int c[MAXLENGTH];  
 struct SElemType/* 栈的元素类型 */  
 {  
   int ord; /* 通道块在路径上的＂序号＂ */  
   PosType seat; /* 通道块在迷宫中的＂坐标位置＂ */  
   int di; /* 从此通道块走向下一通道块的＂方向＂(0～3表示东～北) */  
 };  
#define STACK_INIT_SIZE 10 /* 存储空间初始分配量 */  
 #define STACKINCREMENT 2 /* 存储空间分配增量 */  
 struct SqStack   //SqStack  
 {  
   SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */  
   SElemType *top; /* 栈顶指针 */  
   int stacksize; /* 当前已分配的存储空间，以元素为单位 */  
 }; /* 顺序栈 */  
 bool Pass(PosType b)  
 { /* 当迷宫m的b点的序号为1(可通过路径)，return true, 否则，return false。 */  
   if(m[b.x][b.y]==1)  
     return true;  
   else  
     return false;  
 }  
void FootPrint(PosType a)  
 { /* 使迷宫m的a点的序号变为足迹(curstep) */  
   m[a.x][a.y]=curstep;  
 }  
PosType NextPos(PosType c,int di)  
 { /* 根据当前位置及移动方向，返回下一位置 */  
   PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}}; /* {行增量,列增量} */  
   /* 移动方向,依次为东南西北 */  
   c.x+=direc[di].x;  
   c.y+=direc[di].y;  
   return c;  
 }  
  
 void MarkPrint(PosType b)  
 { /* 使迷宫m的b点的序号变为-1(不能通过的路径) */  
   m[b.x][b.y]=-1;  
 }  
bool InitStack(SqStack *S)  
 { /* 构造一个空栈S */  
   (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));  
   if(!(*S).base)  
     exit(1); /* 存储分配失败 */  
   (*S).top=(*S).base;  
   (*S).stacksize=STACK_INIT_SIZE;  
   return true;  
 }  
bool Push(SqStack *S,SElemType e)  
 { /* 插入元素e为新的栈顶元素 */  
   if((*S).top-(*S).base>=(*S).stacksize) /* 栈满，追加存储空间 */  
   {  
     (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));  
     if(!(*S).base)  
       exit(1); /* 存储分配失败 */  
     (*S).top=(*S).base+(*S).stacksize;  
     (*S).stacksize+=STACKINCREMENT;  
   }  
   *((*S).top)++=e;  
   return true;  
 }  
 bool StackEmpty(SqStack S)  
 { /* 若栈S为空栈，则返回TRUE，否则返回FALSE */  
   if(S.top==S.base)  
     return true;  
   else  
     return false;  
 }  
bool Pop(SqStack *S,SElemType *e)  
 { /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */  
   if((*S).top==(*S).base)  
     return false;  
   *e=*--(*S).top;  
   return true;  
 }  
bool MazePath(PosType start,PosType end) /* 算法3.3 */  
 { /* 若迷宫maze中存在从入口start到出口end的通道，则求得一条 */  
   /* 存放在栈中(从栈底到栈顶)，并返回TRUE；否则返回FALSE */  
   SqStack S;  
   PosType curpos;  
   SElemType e;  
   InitStack(&S);  
   curpos=start;  
   do  
   {  
     if(Pass(curpos))  
     { /* 当前位置可以通过，即是未曾走到过的通道块 */  
       FootPrint(curpos); /* 留下足迹 */  
       e.ord=curstep;  
       a[curstep]=e.seat.x=curpos.x;  
       b[curstep]=e.seat.y=curpos.y;  
       c[curstep]=e.di=0;  
       Push(&S,e); /* 入栈当前位置及状态 */  
       curstep++; /* 足迹加1 */  
       if(curpos.x==end.x&&curpos.y==end.y) /* 到达终点(出口) */  
         return true;  
       curpos=NextPos(curpos,e.di);  
     }  
     else  
     { /* 当前位置不能通过 */  
       if(!StackEmpty(S))  
       {  
         Pop(&S,&e); /* 退栈到前一位置 */  
         curstep--;  
         while((e.di==3) && (!StackEmpty(S))) /* 前一位置处于最后一个方向(北) */  
         {  
           MarkPrint(e.seat); /* 留下不能通过的标记(-1) */  
           Pop(&S,&e); /* 退回一步 */  
           curstep--;  
         }  
         if(e.di<3) /* 没到最后一个方向(北) */  
         {  
           e.di++; /* 换下一个方向探索 */  
           Push(&S,e);  
       a[curstep]=e.seat.x=curpos.x;  
       b[curstep]=e.seat.y=curpos.y;  
       c[curstep]=e.di;  
           curstep++;  
           curpos=NextPos(e.seat,e.di); /* 设定当前位置是该新方向上的相邻块 */  
         }  
       }  
     }  
   }while(!StackEmpty(S));  
   return false;  
 }  
  
 void Print(int x,int y)  
 { /* 输出迷宫的解 */  
   int i,j;  
   for(i=0;i<x;i++)  
   {  
     for(j=0;j<y;j++)  
   cout<<'/t'<<m[i][j]<<" ";  
     cout<<endl;  
   }  
 }  
//stack.h  
   
int main()  
 {  
   PosType begin,end;  
   int i,j,x,y,x1,y1;  
   cout<<"请输入迷宫的行数,列数(包括外墙)：";  
   cin>>x>>y;  
   for(i=0;i<x;i++) /* 定义周边值为0(同墙) */  
   {  
     m[0][i]=1; /* 行周边 */  
     m[x-1][i]=1;  
   }  
   for(j=1;j<y-1;j++)  
   {  
     m[j][0]=1; /* 列周边 */  
     m[j][y-1]=1;  
   }  
   for(i=1;i<x-1;i++)  
     for(j=1;j<y-1;j++)  
       m[i][j]=1; /* 定义通道初值为1 */  
   cout<<"请输入迷宫内墙单元数：";  
   cin>>j;  
   cout<<"请依次输入迷宫内墙每个单元的行数,列数："<<endl;  
   for(i=1;i<=j;i++)  
   {  
    cin>>x1>>y1;  
     m[x1][y1]=0; /* 定义墙的值为0 */  
   }  
   cout<<"迷宫结构如下:"<<endl;  
   Print(x,y);  
   cout<<"请输入起点的行数,列数：";  
   cin>>begin.x>>begin.y;  
   cout<<"请输入终点的行数,列数：";  
   cin>>end.x>>end.y;  
   if(MazePath(begin,end)) /* 求得一条通路 */  
   {  
    cout<<"此迷宫从入口到出口的一条路径如下:"<<endl;  
       Print(x,y); /* 输出此通路 */  
    for(i=1;i<curstep;i++)  
    cout<<a[i]<<" "<<b[i]<<" "<<c[i]<<endl;  
   }  
   else  
    cout<<"此迷宫没有从入口到出口的路径"<<endl;  

   return 0;
}  
