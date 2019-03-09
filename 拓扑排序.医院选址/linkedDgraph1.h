#ifndef linkedDgraph1_
#define linkedDgraph1_

#include<iostream>
#include "graphChain.h"
#include "stack.h" 
using namespace std;
class linkedDgraph1
{
	public:
		linkedDgraph1(int num);
		//~linkedDgraph1();
		int numberOfVertices(); 
		int numberOfEdges();
		bool existsPoint(int);
		bool existsEdge(int ,int);
		void insertEdge(int ,int,int);
		void eraseEdge(int,int);
		void erasePoint(int );
		int getWeight(int,int);
		int degree(int );
		int inDegree(int );
		int outDegree(int );
		bool topologicalOrder(int *);
		int course(pair<int,int> *,int ,int **);
		void shortPaths(int ,int *,int *); 
	private:
		int *point;
		int verticeNumber;
		int edgeNumber;	
		int num1;
		graphChain<int> *g; 
};
linkedDgraph1::linkedDgraph1(int num)
{   verticeNumber=0;
    num1=num;
    edgeNumber=0;
    point=new int[100];
    for(int i=0;i<100;i++)
    point[i]=0;
	g=new graphChain<int> [100];
}
int linkedDgraph1::numberOfVertices()
{   
	return verticeNumber;
}
int linkedDgraph1::numberOfEdges()
{   
   /* for(int i=1;i<=verticeNumber;i++)
        { graphNode<int> *p=g[i].first();
		  while(p!=NULL)
		 {
		 	edgeNumber++;
		 	p=p->next;
		 }
        }*/
	return edgeNumber;
}
bool linkedDgraph1::existsEdge(int i,int j)
{  graphNode<int> *p=g[i].first(); 
   while(p!=NULL)
   {
   	 if(p->element==j)
   	  return true;
   	 else
   	  p=p->next;
   }
   return false;
}
void linkedDgraph1::eraseEdge(int i,int j)
{
	g[i].erase(j);
	if(g[i].first()==NULL)
	verticeNumber--;
	edgeNumber--;
}
int linkedDgraph1::getWeight(int i,int j)
{ 
	graphNode<int> *t=g[i].first();
	while(t!=NULL)
	{
		if(t->element==j)
		return t->weight;
		else
		t=t->next;
	} 
	return 100;
}
void linkedDgraph1::insertEdge(int i,int j,int theWeight)
{   g[i].insert(j,theWeight);
    int ii=0,key=0;
	 while(ii<100&&key==0)
	   {
	    if(i==point[ii])
	    key=1;
	    ii++;
	   } 
	 if(key==0)
	 point[verticeNumber++]=i;  
       ii=0,key=0;
	 while(ii<100&&key==0)
	   {
	    if(j==point[ii])
	    key=1;
	    ii++;
	   } 
	 if(key==0)
	 point[verticeNumber++]=j;  
	edgeNumber++; 
}
int linkedDgraph1::inDegree(int j)
{       int a=0;
      for(int i=1;i<=verticeNumber;i++)
        { graphNode<int> *p=g[i].first();
		  while(p!=NULL)
		 {  if(p->element==j)
		 	a++;
		 	p=p->next;
		 }
        }
	return a;
}
int linkedDgraph1::outDegree(int j)
{
	int a=0;
    	graphNode<int> *p=g[j].first();
    	while(p!=NULL)	
       {
         a++;
         p=p->next;
	   } 
	   return a;
}
int linkedDgraph1::degree(int i)
{
	return  inDegree(i)+outDegree(i);
}
bool linkedDgraph1::topologicalOrder(int *theOrder)
      {// Return false iff the digraph has no topological order.
       // theOrder[0:n-1] is set to a topological order when
       // such an order exists.
         // make sure this is a digraph
         //if (!directed())
           // throw undefinedMethod
            //("graph::topologicalOrder() not defined for undirected graphs");
         int n = verticeNumber;
         // compute in-degrees
         int *indegree = new int [n + 1];
         //fill(indegree + 1, indegree + n + 1, 0);
         for (int i = 1; i <= n; i++)
         {// edges out of vertex i
               indegree[i]=inDegree(i);
               
         }  
         // stack vertices with zero in-degree
         stack<int> astack(100);
         for (int i = 1; i <= n; i++)
            if (indegree[i] == 0)
               {
			    astack.push(i);
			   }
         // generate topological order
         int j = 0;  // cursor for array theOrder
         while (!astack.empty())
         {// select from stack
            int t = astack.top();
            astack.pop();
            theOrder[j++] = t;
            for(int i=1;i<=n;i++)
            {
			    if(existsEdge(t,i))
                {
				 indegree[i]--;
                 if(indegree[i]==0)
                 {
				  astack.push(i);
                  
                 }
               }
			}
         }
         return (j == n);
      }
int linkedDgraph1::course(pair<int,int> *a,int c,int **b)
{   for(int i=0;i<c;i++)
         {  
		    insertEdge(a[i].first,a[i].second,1);
		 }
	int number=0;
	int n=verticeNumber;
	int *indegree=new int[num1+1];
	for(int i=1;i<=num1;i++)
	indegree[i]=inDegree(i);
	stack<int> astack(100);
	while(n!=0)
	{      int j=0;
		 for(int i=1;i<=num1;i++)
		{    
			if(indegree[i]==0)
			{ 
			  b[number][j++]=i;
			  //cout<<i<<" ";
	          astack.push(i);  
		    }
		}
		   number++;
		   //cout<<number<<" ";
		   while(!astack.empty())
			{  int t=astack.top();
			   n--;
			 //  cout<<verticeNumber<<" ";
			   indegree[t]=-1;
			   astack.pop();
			   for(int i=1;i<=num1;i++)
			     if(existsEdge(t,i))
			      indegree[i]--;	
			} 
	}
	return number;
}
bool linkedDgraph1::existsPoint(int i)
{
	if(g[i].first()!=NULL)
	return true;
	else
	return false;
}
void linkedDgraph1::erasePoint(int a)
{   for(int i=1;i<=verticeNumber;i++)
         if(existsEdge(i,a))
			  eraseEdge(i,a);
    for(int i=1;i<=verticeNumber;i++)
         if(existsEdge(a,i))
            eraseEdge(a,i);
            //verticeNumber--;
}
void linkedDgraph1::shortPaths(int sourceVertex,int *distanceFromSource,int *predecessor)
{
	graphChain<int> newReachableVertices;
	for(int i=1;i<=num1;i++)
	{
		distanceFromSource[i]=getWeight(sourceVertex,i);
		if(distanceFromSource[i]==100)//100代表着不存在此边 
		  predecessor[i]=-1;
		else
		{
			predecessor[i]=sourceVertex;
			newReachableVertices.insert(i,0);//插入此节点 
		}
	}
	 distanceFromSource[sourceVertex]=0;
		  predecessor[sourceVertex] =0;
		  while(!newReachableVertices.empty())
		  {  
		     graphNode<int> *p=newReachableVertices.first();
		     int v=p->element;
		     p=p->next;
		     while(p!=NULL)
			 {
			 	int w=p->element;
			 	p=p->next;
			 	if(distanceFromSource[w]<distanceFromSource[v])
			 	  v=w;
			 	  
			 }
		     newReachableVertices.erase(v);
		     for(int j=1;j<=num1;j++)
			 {
			 	if(getWeight(v,j)!=100&&predecessor[j]==-1||distanceFromSource[j]>distanceFromSource[v]+getWeight(v,j))
			 	{
			 		
			 		distanceFromSource[j]=distanceFromSource[v]+getWeight(v,j);
					 if(predecessor[j]==-1)
					   newReachableVertices.insert(j,0);
					  predecessor[j]=v; 			 		
				 }
			 }
		     
		  }
		  
		  
}
#endif
