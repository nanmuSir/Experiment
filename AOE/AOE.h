#ifndef CIRCLE_H
#define CIRCLE_H
#include <iostream> 
#include <cstdlib> 
#include <cstdio> 
#include <cstring> 
#include <queue> 
#include <stack> 
using namespace std; 
 
const int MAXN = 1010; //顶点个数最大  
const int MAXM = 10010; //边数最大  
template<class T>
class AOE
{
	public:
        AOE();
        void init();
        void read_graph(int u, int v, int w, int id);
        void toposort();
        void CriticalPath();
        void read_case();
        void get(int p,int q);
    private:
    	int n, m; //顶点个数，边条数 
    	int v,w,id,u;
        int cnt; 
        int first[MAXN], topo[MAXN]; //表头指针 
        int ind[MAXN], outd[MAXN]; //顶点入度，出度 
        int tot; 
        int Ee[MAXN], El[MAXN], E[MAXN], L[MAXN]; 
        /*Ee表示事件最早可能发生时间，El表示事件最迟允许发生时间*/ 
        /*E表示活动最早可能发生时间，L表示活动最迟允许发生时间*/
    struct Edge 
{ 
    int v, w; 
    int id; 
    int next; 
}edge[MAXM];  
} ;

 
template<class T>
AOE<T>::AOE()
{
    
}

template<class T>
void AOE<T>::get(int p,int q)
{
	n=p;
	m=q;
}
template<class T>
void AOE<T>::init() 
{ 
    cnt = 0; 
    tot = 0; 
    memset(first, -1, sizeof(first));  //char型初始化函数
    memset(ind, 0, sizeof(ind));       //头文件：<string.h> 或 <memory.h>
    memset(outd, 0, sizeof(outd));     //函数原型：void *memset(void *s , int ch , size_t  n )
    memset(Ee, 0, sizeof(Ee));         //memset(结构体/数组名 , "用于替换的字符“ , 前n个字符 );
    memset(E, 0, sizeof(E));           //函数解释：将s中的前n个字节用ch替换并且返回s
    memset(L, 0, sizeof(L));           //函数作用：在一段内存块中填充某一个给定的值，常用于较大的对结构体和数组的清零操作。
    
} 

template<class T>
void AOE<T>::read_graph(int u, int v, int w, int id) //int u, int v, int w, int id
{ 
    edge[cnt].v = v, edge[cnt].w = w, edge[cnt].id = id; 
    edge[cnt].next = first[u], first[u] = cnt++; 
} 

template<class T>
void AOE<T>::toposort() //拓扑排序  
{                       //（u，v)∈E(e)  u在线性序列中出现在v之前 
    queue<int> q; 
    for(int i = 0; i < n; i++) if(!ind[i]) q.push(i); //在有向图中选一个入度为0的顶点，并输出 
    while(!q.empty())          //重复操作，直至图中不含顶点 
    {                          //若图中仍含顶点，所有顶点入度均不为0，则该图中有环 
        int x = q.front(); 
		q.pop(); 
        topo[++tot] = x; 
        for(int e = first[x]; e != -1; e = edge[e].next) //删除所有与其有关的边 
        { 
            int v = edge[e].v, w = edge[e].w; 
            if(--ind[v] == 0) q.push(v); 
            if(Ee[v] < Ee[x] + w) //求出各个顶点Ee值  
            { 
                Ee[v] = Ee[x] + w; 
            } 
        } 
    } 
} 
//找关键路径并输出 
template<class T>
void AOE<T>::CriticalPath() 
{ 
    toposort(); 
    int top = tot; 
    for(int i = 0; i < n; i++) El[i] = Ee[n-1]; //初始化顶点事件的最迟发生时间  
    while(top) //逆拓扑排序求顶点El的值  
    { 
        int x = topo[top--]; 
        for(int e = first[x]; e != -1; e = edge[e].next) 
        { 
            int v = edge[e].v, w = edge[e].w; 
            if(El[x] > El[v] - w) 
            { 
                El[x] = El[v] - w; 
            } 
        } 
    } 
    for(int u = 0; u < n; u++) //求出E,L关键活动  
    { 
        for(int e = first[u]; e != -1; e = edge[e].next) 
        { 
            int v = edge[e].v, id = edge[e].id, w = edge[e].w; //id代表活动的标号  
            E[id] = Ee[u], L[id] = El[v] - w; 
            if(E[id] == L[id]) //相等  是关键活动  
            { 
                printf("a%d : %d->%d\n", id, u, v); 
            } 
        } 
    } 
} 

template<class T>
void AOE<T>::read_case() 
{ 
    init();
    for(int i = 1; i <= m; i++) 
    { 
        int u, v, w; //出，入，权值
		cout<<"a"<<i<<":"; 
        scanf("%d%d%d", &u, &v, &w); //输入出，入，权值 
        read_graph(u,v,w,i); //read_graph 
        outd[u]++, ind[v]++; 
    } 
} 
#endif
