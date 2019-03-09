#include <iostream>
#include<stdio.h>  
#include<stdlib.h>
#include<string>
#include<math.h>
using namespace std; 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	cout<<"请输入数字的个数："<<endl;
	int num;
	cin>>num;
	int shuzu[num];
	cout<<"请输入"<<num<<"个数字，以空格隔开："<<endl; 
	for(int i=0;i<num;i++)
    scanf("%d",&shuzu[i]);
    int temp[num*2];
    int n=0;
    int sum=0;
    for(int i=0;i<num;i++)
    {
    for(int j=i+1;j<num;j++)
    {
     n+=j-1;
     abs(shuzu[i]-shuzu[j])>>temp[n];
     sum++;
    }
	n=num-1;
    }
	int minIndex=0;
	for(int i=0;i<sum;i++)
	{
		cout<<temp[i]<<" "<<endl;
	 if(temp[minIndex]>temp[i])//如果找到更小的
        {  
            minIndex=i;//记下更小的元素的下标
        }  
    }
	printf("最小差值=%d\n",abs(temp[minIndex])); 
	return 0;
}
