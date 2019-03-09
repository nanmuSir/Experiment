#include <iostream>
using namespace std;
template <class T>
class allSort
{
  public:
  	allSort1(T *,int);
  	allSort2(T *,int ,int);
  	allSort3(T *,int ,int, T *);
        void selectionSort();//及时终止的选择排序
        void bubbleSort();//及时终止的冒泡排序
        void insertionSort();//插入排序
        void radixSort();//基数排序
        void quickSort();//快速排序
        void mergeSort();//归并排序
  private:
  	    T *a;
  	    int n;
};
template<class T>
allSort<T>::allSort(T *b,int arrayLength)
{ 
  if(n<1)
  {
  	cout<<"enter a correct number:";
  }
  a=&b[0];
  n=arrayLength;
} 
template<class T>

//及时终止的选择排序
void allSort<T>1::selectionSort()
{
  bool sorted = false;
  for(int size=n;!sorted&&(size-1);size--)
  {
    int indexOfMax=0;
    sorted = true;  //查找最大元素
    for(int i=1;i<size;i++)
       if(a[indexOfMax]<a[i]) indexOfMax=i;
       else sorted=false;  //无序
    swap(a[indexOfMax],a[size-1]);
  }
}

//及时终止的冒泡排序
bool bubble(int a[],int n)
{//把数组a【0：n-1】中的最大元素移到最右端
  bool swapped = false;//目前为止未交换
  for(int i=0;i<n-1;i++)
  if(a[i]>a[i+1])
  {
  	swap(a[i],a[i+1]);
  	swapped=true;//交换 
   } 
   return swapped;
}

template<class T>
void allSort1<T>::bubbleSort()
{
	for(int i=n;i>1&&bubble(a,i);i--);
}

//插入排序
void insert(int a[],int n,const int& x)
{//把x插入有序数组a【0：n-1】 
	int i;
	for(i=n-1;i>=n&&x<a[i];i--) a[i+1]=a[i];
	a[i+1]=x;
}

template<class T>
void allSort1<T>::insertionSort()
{//实施插入排序 
	for(int i=1;i<n;i++)
	{//把a【i】插入到a【0：i-1】中 
		int t=a[i];
		int j;
		for(j=i-1;j>=0&&t<a[j];j--) a[j+1]=a[j];
		a[j+1]=t;
	}
}

//基数排序
int maxbit(int a[], int n)   
{  //求数据的最大位数,决定排序次数
    int d = 1; //保存最大的位数  
    int p = 10;  
    for(int i = 0; i < n; ++i)  
    {  
        while(a[i] >= p)  
        {  
            p *= 10;  
            ++d;  
        }  
    }  
    return d;  
}  

template<class T>
void allSort1<T>::radixSort()   
{  //进行排序 
    int d = maxbit(a, n);  
    int tmp[n];  
    int count[10]; //计数器  
    int i, j, k;  
    int radix = 1;  
    for(i = 1; i <= d; i++) //进行d次排序  
    {  
        for(j = 0; j < 10; j++)  
            count[j] = 0; //每次分配前清空计数器  
        for(j = 0; j < n; j++)  
        {  
            k = (a[j] / radix) % 10; //统计每个桶中的记录数  
            count[k]++;  
        }  
        for(j = 1; j < 10; j++)  
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶  
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中  
        {  
            k = (a[j] / radix) % 10;  
            tmp[count[k] - 1] = a[j];  
            count[k]--;  
        }  
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中  
            a[j] = tmp[j];  
        radix = radix * 10;  
    }  
}  

//快速排序
template<class T>
void allSort2<T>::quickSort()  //int a[], int l, int r
{  //通过一趟排序将要排序的数据分割成独立的两部分，
//其中一部分的所有数据都比另外一部分的所有数据都要小，
//然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，
//以此达到整个数据变成有序序列
    if (l< r)  
    {        
        int i = l, j = r, x = a[l];  
        while (i < j)  
        {  
            while(i < j && a[j]>= x) // 从右向左找第一个小于x的数  
                j--;   
            if(i < j)  
                a[i++] = a[j];  
            while(i < j && a[i]< x) // 从左向右找第一个大于等于x的数  
                i++;   
            if(i < j)  
                a[j--] = a[i];  
        }  
        a[i] = x;  
        quickSort(a, l, i - 1); // 递归调用  
        quickSort(a, i + 1, r);  
    }  
} 

void merge(int *a,int start,int end,int *result)//
{
    int left_length = (end - start + 1) / 2 + 1;//左部分区间的数据元素的个数
    int left_index = start;
    int right_index = start + left_length;
    int result_index = start;
    while(left_index < start + left_length && right_index < end+1)
    {
        //对分别已经排好序的左区间和右区间进行合并
        if(a[left_index] <= a[right_index])
            result[result_index++] = a[left_index++];
        else
            result[result_index++] = a[right_index++];
    }
    while(left_index < start + left_length)
        result[result_index++] = a[left_index++];
    while(right_index < end+1)
        result[result_index++] = a[right_index++];
}
template<class T>
void allSort<T>::mergeSort()//int *a, int start, int end, int *result
{
    if(1 == end - start)//如果区间中只有两个元素，则对这两个元素进行排序
    {
        if(a[start] > a[end])
        {
            int temp  = a[start];
            a[start] = a[end];
            a[end] = temp;
        }
        return;
    }
    else if(0 == end - start)//如果只有一个元素，则不用排序
        return;
    else
    {
        //继续划分子区间，分别对左右子区间进行排序
        mergeSort(a,start,(end-start+1)/2+start,result);
        mergeSort(a,(end-start+1)/2+start+1,end,result);
        //开始归并已经排好序的start到end之间的数据
        merge(a,start,end,result);
        //把排序后的区间数据复制到原始数据中去
        for(int i = start;i <= end;++i)
            a[i] = result[i];
    }
}
int main()
{
  int a[10];
  cout<<"输入的无序整数个数为（至多十个）："<<endl;
  int n;
  cin>>n;
  for(int i=0;i<n;i++) cin>>a[i];
  cout<<"您输入的无序数组为：[";
  for(int i=0;i<n;i++) cout<<a[i]<<" ";
  cout<<"]"<<endl;
  
  allSort<int> s(a,n);
  s.selectionSort();
  cout<<"选择排序后的数组为："<<"[";
  for(int i=0;i<n;i++) cout<<a[i]<<" ";
  cout<<"]"<<endl;
  
  s.bubbleSort();
  cout<<"冒泡排序后的数组为："<<"[";
  for(int i=0;i<n;i++) cout<<a[i]<<" ";
  cout<<"]"<<endl;
  
  s.insertionSort();
  cout<<"插入排序后的数组为："<<"[";
  for(int i=0;i<n;i++) cout<<a[i]<<" ";
  cout<<"]"<<endl;
  
  s.radixSort(); 
  cout<<"基数排序后的数组为："<<"[";
  for(int i=0;i<n;i++) cout<<a[i]<<" ";
  cout<<"]"<<endl;
  
  allSort<int> s(a,n,n);
  s.quickSort();
  cout<<"快速排序后的数组为："<<"[";
  for(int i=0;i<n;i++) cout<<a[i]<<" ";
  cout<<"]"<<endl;
  
  allSort<int> s(a,n,n,result);
  const int length = n;
  int result[length];
  s.mergeSort();
  cout<<"归并排序后的数组为："<<"[";
  for(int i=0;i<n;i++) cout<<a[i]<<" ";
  cout<<"]"<<endl;
  return 0;
  
  
}
