#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include<iostream>
using namespace std;
const int dd[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
char map[33][53];
int d,fx,fy,score;
bool eat;
struct body
{
    int x,y;
    body *last,*next;
    body(){last=next=NULL;}
}*head;
int Rand(int l,int r)
{
    return rand()%(r-l+1)+l;
}
void init()
{
    for(int i=0;i<22;i++)
        for(int j=0;j<52;j++)
            map[i][j]=' ';
    for(int i=0;i<52;i++)
        map[0][i]=map[21][i]='#';
    for(int i=0;i<22;i++)
        map[i][0]=map[i][51]='#';
    srand((unsigned)time(NULL));
    head=new body;
    head->x=Rand(5,15),head->y=Rand(10,40);
    d=Rand(0,3);
    switch(d)
    {
        case 0:map[head->x][head->y]='|';map[head->x+1][head->y]='|';break;
        case 1:map[head->x][head->y]='-';map[head->x][head->y+1]='-';break;
        case 2:map[head->x][head->y]='|';map[head->x-1][head->y]='|';break;
        case 3:map[head->x][head->y]='-';map[head->x][head->y-1]='-';break;
    }
    body *l=new body;
    *l=*head;
    l->x+=dd[d][0];
    l->y+=dd[d][1];
    head->last=l;
    l->next=head;
    d=(d+2)%4;
    do
    {
        fx=Rand(1,20);fy=Rand(1,50);
    }while(map[fx][fy]!=' ');
    map[fx][fy]='*';
}
void print()
{
    system("cls");
    for(int i=0;i<22;i++)
        puts(map[i]);
    printf("Your score:%d\n",score);
}
void Update(body *u,int x,int y)
{
    if(map[x][y]=='#'||map[x][y]=='-'||map[x][y]=='|')
    {cout<<"Game over!"<<endl;MessageBox(NULL,"Game over!","Game over!",NULL);exit(0);}
    if(u==NULL)return;
    if(u->last!=NULL||eat==0)
        map[u->x][u->y]=' ';
    else
    {
        u->last=new body;
        u->last->next=u;
        u->last->x=u->x;
        u->last->y=u->y;
        score++;
        do
        {
            fx=Rand(1,20);fy=Rand(1,50);
        }while(map[fx][fy]!=' ');
        map[fx][fy]='*';
    }
    char c;
    if(u->x==x)
        c='-';
    if(u->y==y)
        c='|';
    map[x][y]=c;
    if(u->last&&(u->last->x!=u->x||u->last->y!=u->y))Update(u->last,u->x,u->y);
    u->x=x;u->y=y;
}
int main()
{
    init();
    while(1)
    {
        print();
        int x=d;
        for(int i=0;i<=10;i++)
        {
            if(GetKeyState('S')<0&&d!=2)
                x=0;
            if(GetKeyState('D')<0&&d!=3)
                x=1;
            if(GetKeyState('W')<0&&d!=0)
                x=2;
            if(GetKeyState('A')<0&&d!=1)
                x=3;
            Sleep(10);
        }
        d=x;
        eat=(map[head->x+dd[d][0]][head->y+dd[d][1]]=='*');
        Update(head,head->x+dd[d][0],head->y+dd[d][1]);
    }
   
    system("pause");
     return 0;
}
