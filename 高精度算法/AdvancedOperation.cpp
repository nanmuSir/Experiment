#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include<string.h>  
#define MaxLen 200 
#include "AdvancedOperation.h"
using namespace std;
		int i;	 
int main(int argc, char** argv) {
		
	AdvancedOperation<int> g;
	g.translate();
	cout<<"a+b=";
	
	g.add();
	cout<<endl;
	
	cout<<"a-b=";
	g.sub();
	cout<<endl;
	
	cout<<"a*b=";
	g.multi();
	cout<<endl;
	
	cout<<"a/b=";
	g.divide();
	cout<<endl;
	
	system("pause");
	return 0;
}
