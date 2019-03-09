#ifndef  graphNode_ 
#define  graphNode_
#include<iostream>
using namespace std;
template<class T>
struct graphNode
{
	T element;
	int weight;
	graphNode<T> *next;
	graphNode<T> *pre;
	graphNode(T theElement,int theWeight,graphNode<T> *thePre,graphNode<T> *theNext)
	{
		element=theElement;
		weight=theWeight;
		pre=thePre;
		next=theNext;
	}
	graphNode(T theElement,int theWeight)
	{
		element=theElement;
		weight=theWeight;
		pre=NULL;
		next=NULL;
	}
	graphNode()
	{
		pre=next=NULL;
	}
};
#endif
