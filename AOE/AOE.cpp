#include <iostream> 
#include <cstdlib> 
#include <cstdio> 
#include <cstring> 
#include <queue> 
#include <stack> 
#include "AOE.h"
using namespace std; 

int n, m; //顶点个数，边条数 
int cnt; 

int main() 
{ 
    cout<<"请输入顶点个数和边的条数："<<endl; 
    AOE<int> aoe; 
    while(~scanf("%d%d", &n, &m)) 
    { 
        aoe.get(n,m);
        aoe.read_case(); 
        printf("\n关键路径:\n"); 
        aoe.CriticalPath(); 
    } 
    return 0; 
} 
