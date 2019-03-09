#include<iostream>
using namespace std;
template<class T>
class sort
	{
	public:
		sort(T *,int);
       void printarray()
	   {
	   	 for(int i=0;i<n;i++)
	   	  {
			 cout<<a[i];
	   	  cout<<" ";
	   }cout<<endl;
	   }
		void selectSort()
		{ int min,indexofMin;
		  for(int i=0;i<n-1;i++)
          { min=a[i];indexofMin=i;bool b=false;
		    for(int j=i+1;j<n;j++)
             {if(min>a[j])
               { min=a[j];//把较小的值存入min中 
                 indexofMin=j;//记录最小值的位置 
			   }
             }
           a[indexofMin]=a[i];//完成一次比较后交换响应的位置 
           a[i]=min;
           printarray();
		  }
		}
		void bubbleSort()
		{ int t;
		  for(int i=0;i<n;i++)
		 {  bool  b=false;//设立一个判断是否可以天谴终端的值 
		     for(int j=n-1;j>i;j--)
		     { if(a[j-1]>a[j])//较小的值往前面交换 
			  {
			 	t=a[j];
			 	a[j]=a[j-1];
			 	a[j-1]=t;
			 	b=true;//交换的话改变bool型的值 
			  }
			 }
			 if(!b)
			 break;//没有交换的话退出循环 
		     printarray();
		}}
		void insertSort()
		{ for(int i=1;i<n;i++)
		{
			int t=a[i];
			int j;
			for(j=i-1;j>=0&&t<a[j];j--)
			  a[j+1]=a[j];
			a[j+1]=t;
			printarray();
		 } 
		} 
/*
*求数据的最大位数,决定排序次数
*/
int maxbit(int *a,int) 
{
    int d=1; //保存最大的位数
    int p=10;
    for(int i=0;i<n;++i)
    {
        while(a[i]>=p)
        {
            p*=10;
            ++d;
        }
    }
    return d;
}
void radixsort() //基数排序
{
    int d=maxbit(a,n);
    int tmp[n];
    int count[10]; //计数器
    int i,j,k;
    int radix=1;
    for(i=1;i<=d;i++) //进行d次排序
    {
        for(j=0;j<10;j++)
            count[j] = 0; //每次分配前清空计数器
        for(j=0;j<n;j++)
        {
            k=(a[j]/radix)%10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j=1;j<10;j++)
            count[j]=count[j - 1]+count[j]; //将tmp中的位置依次分配给每个桶
        for(j=n-1;j>=0;j--) //将所有桶中记录依次收集到tmp中
        {
            k=(a[j]/radix)%10;
            tmp[count[k]-1]=a[j];
            count[k]--;
        }
        for(j=0;j<n;j++) //将临时数组的内容复制到data中
            a[j]=tmp[j];
        radix=radix*10;
        printarray();
    }
}
private:
	T *a;
	int n;};
template<class T>
sort<T>::sort(T *b,int arrayLength)
{ 
  if(n<1)
  {
  	cout<<"enter a correct number:";
  }
  a=&b[0];
  n=arrayLength;
} 
int main()
{  cout<<"enter a number:";
   int n;
   cin>>n; 
   int a[n];
   for(int i=0;i<n;i++)
   cin>>a[i];
   sort<int> w(a,n);
   int q;
   cout<<"请选择一种排序方式：1：选择排序 2：冒泡排序 3：插入排序 4：基数排序";
   cin>>q;
   switch(q)
   {
   	case(1):
   		w.selectSort();
   		break;
   	case(2):
   		w.bubbleSort();
   		break;
   	case(3):
	   w.insertSort();
	   break;
	  case(4):
	  w.radixsort(); }
	
}
