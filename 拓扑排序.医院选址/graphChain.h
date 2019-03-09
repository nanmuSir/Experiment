#ifndef graphChain_
#define graphChain_

#include "graphNode.h"
#include<iostream>
using namespace std;
template<class T>
class graphChain
{
	public:
		graphChain();
		//~graphChain();
		void erase(T theElement);
		bool empty() {return listSize==0;}
        int size(){return listSize;}
        T getElement(int theIndex);
        int getWeight(int theIndex);
        int indexOf(const T& theElement);
        void insert(T theElement,int theWeight);
        void insertHead(T theElement,int theWeight);
        graphNode<T> * first(){return firstNode;}
        graphNode<T> * last(){return lastNode;}
        
	class iterator
	{
		public:
			iterator(graphNode<T>* theNode=NULL)
			{ node=theNode;
			}
			T& operator*() const {return node->element;}
			T* operator->() const{return &node->element;}
	        iterator& operator++()
			{
				node=node->next;
				return *this;
			}
			iterator& operator--()
			{
				node=node->pre;
				return *this;
			}
			bool operator!=(const iterator right)const
			{
				return node !=right.node;
			}
			bool operator==(const iterator right)const
			{
				return node==right.node;
			}
			
		private:
				graphNode<T>* node;
	};
//******************************************************* 
	iterator begin()//头指针 
			{
			  return iterator(firstNode);
			}
			
	iterator end()//尾指针 
			{
				return iterator(lastNode);
			}
			
    private:
	int listSize;
	graphNode<T> *firstNode;
	graphNode<T> *lastNode; 
		
}; 
template<class T>
graphChain<T>::graphChain()
{
	listSize=0;
	firstNode=lastNode=NULL;
}
template<class T>
T graphChain<T>::getElement(int theIndex) 
	{ 
	  if(theIndex<listSize)
	  {
	  	graphNode<T>* currentNode=firstNode;
	  	for(int i=0;i<theIndex;i++)
		  {
		  	currentNode=currentNode->next;
		  }
		return currentNode->element;
	  }  
	  else
	  {
	  	cout<<"enter a correct number:";
	  }
	}
	template<class T>
int graphChain<T>::getWeight(int theIndex) 
	{ 
	  if(theIndex<listSize)
	  {
	  	graphNode<T>* currentNode=firstNode;
	  	for(int i=0;i<theIndex;i++)
		  {
		  	currentNode=currentNode->next;
		  }
		return currentNode->weight;
	  }  
	  else
	  {
	  	cout<<"enter a correct number:";
	  }
	}
template<class T>
int graphChain<T>::indexOf(const T& theElement) 
{
        graphNode<T>* currentNode=firstNode;
		int i=0;
		while(currentNode!=NULL&&currentNode->element!=theElement)
		{   currentNode=currentNode->next;
		    i++;
		}		
		if(currentNode==NULL)//线性表中不存在此元素 
		return -1; 
		else
		return i;
}
template<class T>	
void graphChain<T>::erase(T theElement)
{   if(listSize<=0)//如果线性表为空 
	      cout<<"it's empty"<<endl;
	    else if(listSize==1)//如果表中只有一个元素 
          { if(firstNode->element==theElement)//当表头为所要删除的元素时 
		    {
			 firstNode=lastNode=NULL;
		     listSize--;
			}
			else
			cout<<"there is not theElement"<<endl;
	      }
	    else//多个元素的情况 
		{ if(firstNode->element==theElement)//如果第一个元素为要删除的元素 
		   {firstNode=firstNode->next;
		    firstNode->pre=NULL;
		    listSize--;
		   }
		  else if(lastNode->element==theElement)//如果最后一个元素为要删除的元素 
		    {lastNode=lastNode->pre;
		     lastNode->next=NULL;
		     listSize--;
		    }
		  else{//其他情况 
		 graphNode<T>* currentNode=firstNode->next;
		 graphNode<T>* p=firstNode;
		 while(currentNode!=NULL&&currentNode->element!=theElement)//元素不相等就继续循环 
		  { 
		    currentNode=currentNode->next;
			p=p->next;	
	      } 
		 if(currentNode==NULL)//如果线性表中没有这个元素 
		 cout<<"there is no thelement in it"<<endl;
		 else
		  {currentNode->pre->next=currentNode->next;
		   currentNode->next->pre=currentNode->pre;
		   //p->next=currentNode->next;
		   listSize--; 
		  }
	    }
		}
	    
}
template<class T>
void graphChain<T>::insert(T theElement,int theWeight)
	{ if(firstNode==NULL)
	   { 
	     firstNode=new graphNode<T>(theElement,theWeight,firstNode,NULL);
	     lastNode=firstNode;
	   } 
	  else
	  {
	  	graphNode<T>* currentNode=new graphNode<T>(theElement,theWeight,NULL,NULL);
	  	firstNode->pre=currentNode;
        currentNode->next=firstNode;
        firstNode=currentNode;
	  }
	  listSize++;
	}
template<class T>
void graphChain<T>::insertHead(T theElement,int theWeight)
{   T element=theElement;int weight=theWeight;
    graphNode<T> *t=new graphNode<T>(element,weight);
	if(firstNode==NULL)
	firstNode=lastNode=t;
	else
	{  graphNode<T> *q=firstNode->next;
	  firstNode->next=t;
	  t->next=q;	
	}
	listSize++;
} 

#endif
