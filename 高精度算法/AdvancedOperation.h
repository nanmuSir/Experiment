#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include<string.h>  
#define MaxLen 200 
using namespace std;
FILE *fpRead1,*fpRead2,*fp;	
template<class T>
class AdvancedOperation
{
//	int a[],int b[],int c[],int n,int m
	public:
		AdvancedOperation();
		void add();
		void sub();
		void multi();
		int SubStract(int a[], int b[], int n, int m );
		int divide();
		void translate();
	private:
	    int i;
		int c[3000];
		char numberN[1500], numberM[1500];	
		int* a;
		int* b;
		int* r;
		int n, m;
};
template<class T>
AdvancedOperation<T>::AdvancedOperation()
{
    
}
template<class T>
void AdvancedOperation<T>::translate()
{
	//文件读取，存入数组中 
	fpRead1 = fopen("E:\\C++\\高精度算法\\data1.txt", "r");
	if (fpRead1 == NULL){  
        cout<<"Open File Failed."<<endl;  
        exit(0);  
    } 
    //得到文件内数据的长度 
    fseek(fpRead1,0,SEEK_SET);
    fseek(fpRead1,0,SEEK_END);
    long length1=ftell(fpRead1);// length1就是文件的长度
    
    fseek(fpRead1,0,SEEK_SET);     //文件流位置放到开头
	for(i=0;i<length1;i++){   
	    fscanf(fpRead1, "%s", &numberN[i]); //读取单个数据 
    }  	
    
    fpRead2 = fopen("E:\\C++\\高精度算法\\data2.txt", "r");
    if (fpRead2 == NULL){  
        cout<<"Open File failed.\n";  
        exit(0);  
    } 
    //得到文件内数据的长度 
    fseek(fpRead2,0,SEEK_SET);
    fseek(fpRead2,0,SEEK_END);
    long length2=ftell(fpRead2);// length2就是文件的长度
    
    fseek(fpRead2,0,SEEK_SET);  //文件流位置放到开头 
	for(i=0;i<length2;i++){  
    fscanf(fpRead2, "%s", &numberM[i]);  //读取单个数据 
    }  	
	    n = strlen(numberN);m = strlen(numberM);
		a=new int[n];b=new int[m];              //两个和数据等长的中间数组 
		int i, j;
		for (i = 0, j = n - 1; i < n; i++, j--) {//将字符数组转换为整型数数组 
			a[i] = numberN[j] - '0';
		}
		for (i = 0, j = m - 1; i < m; i++, j--) {//将字符数组转换为整型数数组 
			b[i] = numberM[j] - '0';
		}
		cout<<"a为：";
		for(i=n-1;i>=0;i--)cout<<a[i];
		cout<<endl;
		cout<<"b为：";
		for(i=m-1;i>=0;i--)cout<<b[i];
		cout<<endl<<endl;
	
}
template<class T>
void AdvancedOperation<T>::add()
{
		//cout<<"m="<<m<<" n="<<n<<endl;
		r=new int[3000];
		for(i=0;i<3000;i++)r[i]=0;
		
		    if(n>=m)
		{
			for(i=0;i<m;i++)
		    r[i]=a[i]+b[i];
		    
		    for(i=m;i<n;i++){
		    	r[i]+=a[i];
			}
	    }
	        else
	    {
	    	for(i=0;i<n;i++)
		    r[i]=a[i]+b[i];
		    for(i=n;i<m;i++)
			r[i]+=b[i]; 
		}
	
		for (i = 0; i < n + m; i++) {  //进位的处理 
		    if (r[i] >= 10) {
				r[i + 1] += r[i] / 10;
				r[i] %= 10;         
			}
		}
		int j;
		for ( j = 2999; j > 0; j--) {  //从后向前遍历，当最后一位不为零时，即为到达运算结果的最后一位（原数组全为0） 
			if (r[j] != 0)
				break;
		}
		fp=fopen("E:\\C++\\高精度算法\\add.txt","w");
		for (i = j; i >= 0; i--) {
			printf("%d", r[i]);
			fprintf(fp,"%d",r[i]);
		}
		printf("\n");
}
template<class T>
void AdvancedOperation<T>::sub()
{
	    int j;
		for(i=0;i<3000;i++)r[i]=0;
		if(n>=m)                          //做比较，分被减数数组大于减数数组和被减数数组小于减数数组两种情况 
		{                                 //被减数数组大于减数数组 
			for(i=0;i<m;i++)
		    r[i]=a[i]-b[i];
		    for(i=m;i<n;i++)r[i]+=a[i];
	    }
	    else if(n<m)                     //被减数数组小于减数数组 
	    {
	    	for(i=0;i<n;i++)
		    r[i]=a[i]-b[i];
		    for(i=n;i<m;i++)r[i]-=b[i]; 
		}
		//for (j = 2999; j > 0; j--) {  //从后向前遍历，当最后一位不为零时，即为到达运算结果的最后一位（原数组全为0） 
		//	if (r[j] != 0)
		//		break;
		//}  
		for (i = 0; i < j; i++) {  //进位的处理 
		    if (r[i] < 0) {
				r[i + 1] - 1;
				r[i] += 10;         
			}
		}
		for (j = 2999; j > 0; j--) {  //从后向前遍历，当最后一位不为零时， 
			if (r[j] != 0)            //即为到达运算结果的最后一位（原数组全为0）
				break;
		}
		fp=fopen("E:\\C++\\高精度算法\\sub.txt","w");
        for (i = j; i >= 0; i--) {
			printf("%d", r[i]);
			fprintf(fp,"%d",r[i]);
		}
		printf("\n");
}
template<class T>
void AdvancedOperation<T>::multi()
{
		int j;
	    for (i = 0; i < 3000; i++) r[i] = 0; 
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				r[i + j] += a[i] * b[j];    //根据乘法性质来进行运算 
			}
		}
		for (i = 0; i < n + m; i++) {  //进位的处理 
			if (r[i] >= 10) {
				r[i + 1] += r[i] / 10;
				r[i] %= 10;         
			}
		}
		for (j = 2999; j > 0; j--) {  //从后向前遍历，当最后一位不为零时，即为到达运算结果的最后一位（原数组全为0） 
			if (r[j] != 0)
				break;
		}
		fp=fopen("E:\\C++\\高精度算法\\multi.txt","w");
		for (i = j; i >= 0; i--) {
			printf("%d", r[i]);
			fprintf(fp,"%d",r[i]);
		}
		printf("\n");
}
template<class T>
int AdvancedOperation<T>::SubStract(int a[], int b[], int n, int m )
{
	int i;  
    if( n < m )  
        return -1;  
    if( n == m )  
    {                        //判断a > b  
        for( i=n-1; i>=0; i-- )  
        {  
            if( a[i] > b[i] )   //若大，则满足条件，可做减法  
                break;  
            else if( a[i] < b[i] ) //否则返回-1  
                return -1;  
        }  
    }  
    for( i=0; i<=n-1; i++ )  //从低位开始做减法  
    {  
        a[i] -= b[i];  
        if( a[i] < 0 )          //若a<0，则需要借位  
        {  
            a[i] += 10;         //借1当10  
            a[i+1]--;           //高位减1  
        }  
    }
    
    for( i=n-1; i>=0; i-- )       //查找结果的最高位  
        if( a[i] )               //最高位第一个不为0  
            return (i+1);       //得到位数并返回  
    
    return 0;                  //两数相等的时候返回0  
}
template<class T>
int AdvancedOperation<T>::divide()
{
	int j; 
    int nTimes;                 //两大数相差位数  
    int nTemp;                  //Subtract函数返回值  
    for (i = 0; i < 3000; i++) r[i] = 0;   //结果数组全部置零
	//int temp[n];                //temp数组暂存a数组内容，用于求余数
	//for(j=0;j<n;j++)temp[j]=a[j]; 
 
        if( n < m )   //如果被除数小于除数，结果为0  
        {  
            cout<<"0"<<endl;    
        }  
        nTimes = n - m;    //相差位数  
        for ( i=n-1; i>=0; i-- )    //将除数扩大，使得除数和被除数位数相等  
        {  
            if ( i>=nTimes )  
                b[i] = b[i-nTimes];  
            else                     //低位置0  
                b[i] = 0;  
        }  
        m = n;  
        for(j=0; j<=nTimes; j++ )      //重复调用，同时记录减成功的次数，即为商  
        {  
            while((nTemp = SubStract(a,b + j,n,m - j)) >= 0)  
            {  
                n = nTemp;      //结果长度  
                r[nTimes-j]++; //每成功减一次，将商的相应位加1  
            }  
        }  
  
        //输出结果  
        for( i=2999; r[i]==0 && i>=0; i-- );//跳过高位0  
        if( i>=0 ) 
		      {
                for( ; i>=0; i-- )  
                cout<<r[i];
			  }
        else  
            cout<<"0";  
        cout<<endl; 
        cout<<"余数为：";
		for( i=n-1; i>=0; i-- )cout<<a[i];
        cout<<endl; 
        
        fp=fopen("E:\\C++\\高精度算法\\divide.txt","w");
		for (i = j-1; i >= 0; i--) {
			fprintf(fp,"%d",r[i]);
		}
		printf("\n");
		fprintf(fp,"\n%s","余数为：");
		for( i=n-1; i>=0; i-- )fprintf(fp,"%d",a[i]);
		printf("\n");
		
        return 0; 
}
#endif
