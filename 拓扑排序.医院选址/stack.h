#ifndef stack_
#define stack_

#include<iostream>
#include<string>
using namespace std;
template<class T>
class stack
{
	public:
		stack(int n);
		~stack(){delete [] element;}
		bool empty();
		int size();
		T top();
		void pop();
		void push(T theElement); 
    private:
    	T *element;
		int stackTop;
		int listSize;
		int arrayLength; 
};
template<class T>
stack<T>::stack(int n)
{   if(n<=0)
    cout<<"the n must be >0";
    else
	{stackTop=-1;
	 arrayLength=n;
	 listSize=0;
	 element=new T[n];
    }
}
template<class T>
bool stack<T>::empty()
{
	return listSize==0;
}
template<class T>
int stack<T>::size()
{
	return listSize;
}
template<class T>
T stack<T>::top()
{
	return element[stackTop];
}
template<class T>
void stack<T>::pop()
{
	if(listSize==0)
	cout<<"the stack is empty";
	else
	{
		stackTop--;
		listSize--;
	}
}
template<class T>
void stack<T>::push(T theElement)
{
	if(listSize<arrayLength)
	{
	 element[++stackTop]=theElement;
	 listSize++;
    }
    else if(listSize==arrayLength)
	{
		T *elementCopy=new T[arrayLength];
		elementCopy=&element[0];
		delete [] element;
		T *element=new T[2*arrayLength];
			element=&elementCopy[0];
            element[++stackTop]=theElement;
            arrayLength=arrayLength*2;
            listSize++;
	}
}
#endif
