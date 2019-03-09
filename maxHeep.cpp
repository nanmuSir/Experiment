#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
class binaryTreeNode{
	public:
		binaryTreeNode(){
			leftChild=rightChild=0;
		}
		binaryTreeNode(const int &e){
			data=e;
			leftChild=rightChild=0;
		}
		binaryTreeNode(const int&e,binaryTreeNode*l,binaryTreeNode*r){
			data=e;
			leftChild=l;
			rightChild=r;
		}
		int data;
		binaryTreeNode*leftChild,*rightChild;
};
void Travel(binaryTreeNode*roots){
	queue<binaryTreeNode*>q;
	while(roots){
		cout<<roots->data<<" ";
		if(roots->leftChild)q.push(roots->leftChild);
		if(roots->rightChild)q.push(roots->rightChild);
		try{
			roots=q.front();
			q.pop();
		}
		catch(...){
			return;
		}
	}
}
void preOrder(binaryTreeNode *roots){//前序遍历 
			if(roots){
				cout<<roots->data <<" ";
				preOrder(roots->leftChild);//前序遍历左子树
				preOrder(roots->rightChild);//前序遍历右子树 
			} 
		}
void inOrder(binaryTreeNode *roots){//中序遍历 
		if(roots){
		inOrder(roots->leftChild);
		cout<<roots->data<<" ";
		inOrder(roots->rightChild);
		}
}
class MaxHeap{
	public:
		MaxHeap(){
			root=0;
			state=0;
		}
		void MakeHeap(int element,MaxHeap&left,MaxHeap&right);
		int Max(){
			if(!root)return 0;
			return root->data;
		}
		MaxHeap&Insert(const int &x);
		MaxHeap&DeleteMax(int&x);
		MaxHeap&Initialize(int a[],int n);
		void Deactivate(){heap=0;}
		void HeapSort(int a[],int n);
		binaryTreeNode *root,*last,*p_last;
		int state;
		void ConditionOrder(binaryTreeNode*u,int k,int i,binaryTreeNode*temp);
		void Adjust(binaryTreeNode*u);
		binaryTreeNode*LocateLast(binaryTreeNode*u,int k,int i);
	private:
		MaxHeap *heap;
		
};	
void MaxHeap::MakeHeap(int element,MaxHeap&left,MaxHeap&right)	{
	root=new binaryTreeNode(element,left.root,right.root);
	left.root=right.root=0;
	last=p_last=root;
	state++;
}
binaryTreeNode*MaxHeap::LocateLast(binaryTreeNode*u,int k,int i){
	if(k<=1)return u;
	else{
		int n=(int)pow(2.0,k-1);
		int s=n/2;
		if(i<=s)return LocateLast(u->leftChild,k-1,i);
		else return LocateLast(u->rightChild,k-1,i-s);
	}
}
void MaxHeap::ConditionOrder(binaryTreeNode*u,int k,int i,binaryTreeNode*temp){
	int half=(int)pow(2.0,k-2);  //比较插入节点元素与父节点。子节点的大小关系，并插入 
	if(u->data<temp->data){
		swap(u->data,temp->data); 
	}
	if(!u->leftChild||!u->rightChild){
		if(!u->leftChild){
			u->leftChild=temp;
			p_last=u;
			state++;
		}
		else{
			u->rightChild=temp;
			p_last=u;
			state++;
		}
	}
	else{
		if(i<=half)ConditionOrder(u->leftChild,k-1,i,temp);
		else ConditionOrder(u->rightChild,k-1,i-half,temp);
	}
}
MaxHeap&MaxHeap::Insert(const int&x){ //插入操作，用于插入新节点 
	if(root){           //插入的新节点需要经过调整，重新进行 
		int k=(int)(log((double)(state))/log(2.0))+1; 
		int index=state-(int)(pow(2.0,k-1)-1);
		int p_index=index/2+1;
		binaryTreeNode *temp=new binaryTreeNode(x);
		last=temp;
		if(index==(int)(pow(2.0,k-1))){
			p_index=1;
			ConditionOrder(root,k,p_index,temp);
			}
			else ConditionOrder(root,k-1,p_index,temp);
	}
	else{
		root=new binaryTreeNode(x);
		last=p_last=root;
		state++;
	}
	return *this;
}
void MaxHeap::Adjust(binaryTreeNode*u){ //调整堆，用于排序的顺利进行 
        if(!u->leftChild&&!u->rightChild)return;
        else if(u->leftChild&&u->rightChild){
              if(u->leftChild->data>u->rightChild->data){
                  if(u->data<u->leftChild->data){
                      swap(u->data,u->leftChild->data);
                      Adjust(u->leftChild);
                  }
              }
              else{
                  if(u->data<u->rightChild->data){
                      swap(u->data,u->rightChild->data);
                      Adjust(u->rightChild);
                  }
              }
        }
}
MaxHeap&MaxHeap::DeleteMax(int&x){ // 删除根节点 
        if(!root)exit(1);
        else if(!last){
             x=root->data;
             state=0;
             root=0;
        }
        else{  
             x=root->data;
             root->data=last->data;
             int k=(int)(log((double)(state))/log((double)(2)))+1;
             int index=state-(int)(pow(2.0,k-1)-1);
             Adjust(root);
             if(index%2)p_last->leftChild=0;
             else p_last->rightChild=0;
             delete last;
             state--;
             k=(int)(log((double)(state-1))/log((double)(2)))+1;
             index=state-1-(int)(pow(2.0,k-1)-1);
             int p_index=index/2+1;
             if(index==(int)(pow(2.0,k-1))){
                 p_index=1;
                 p_last=LocateLast(root,k,p_index);
             }
             else p_last=LocateLast(root,k-1,p_index);
             if(!p_last->rightChild)last=p_last->leftChild;
             else last=p_last->rightChild;
       }
       return *this;
}
MaxHeap&MaxHeap::Initialize(int a[],int n){ //初始化大根堆 
       MaxHeap LMaxHeap,RMaxHeap;
       MakeHeap(a[0],LMaxHeap,RMaxHeap);
       for(int i=1;i<n;i++)Insert(a[i]);
       return * this;
} 
void MaxHeap::HeapSort(int *a,int n){
       //创建一个最大堆
       MaxHeap maxHeap;
       maxHeap.Initialize(a,n);
       int x;
       for(int i=n-1;i>=0;i--){
          maxHeap.DeleteMax(x);
          a[i]=x;
       }
}
/*class HTNode{
    public:
       int weight;//权重
       int parent,lchild,rchild;
};
typedef HTNode* HuffmanTree;

HuffmanTree HuffmanTreeCoding(char**&HC,int w[],int a[],int n);
void Select(HuffmanTree HT,int n,int&s1,int&s2) ;
void HTEcode(char**&HC,int w[],int code[],int codeLen,int a[],int aLen);
 
void Select(HuffmanTree HT,int n,int&s1,int&s2){
      int i=1,j;
      while(HT[i].parent!=0)
          i++;
          j=i+1;
      while(HT[j].parent!=0)
          j++;
      if(HT[i].weight>HT[j].weight){
          s1=j;//权重小的
          s2=i;
      }
      else{
          s1=i;
          s2=j;
      }
      i=j+1;
      while(i<=n){
          if(HT[i].parent!=0)i++;
          else if(HT[i].weight<HT[s1].weight){
             s2=i;
             s1=i;
          }
          else if(HT[i].weight<HT[s2].weight){
             s2=i;
             i++;
          }
      }
}
HuffmanTree HuffmanCoding(char**&HC,int w[],int a[],int n){
      int i,start,c,f;
      HTNode*p;
      char *cd;
      if(n<1)return NULL;
      int m=2*n-1;
      //定义一个有m+1个节点的HuffmanTree
      HuffmanTree HT=new HTNode[m+1];
      //初始化
      for(p=HT+1,i=1;i<=n;i++,p++){
         p->weight=w[i-1];
         p->lchild=0;
         p->rchild=0;
         p->parent=0;
      }
      int s1,s2;
      for(;i<=m;++i){
         Select(HT,i-1,s1,s2);
         HT[s1].parent=i;
         HT[s2].parent=i;
         HT[i].parent=0;
         HT[i].lchild=s1;
         HT[i].rchild=s2;
         HT[i].weight=HT[s1].weight+HT[s2].weight;
      }
      HC=new char*[n];
      cd=new char[n];
      cd[n-1]='\0';
      for(i=1;i<n;++i){
         start=n-1;
         for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){
              if(HT[f].lchild==c)cd[--start]='0';
              else cd[--start]='1';
         }
         HC[i-1]=new char[n-start];
         strcpy(HC[i-1],&cd[start]);
     }
     return HT;
}
void HTEcode(char**&HC,int w[],int code[],int codeLen,int a[],int aLen){
     int j;
     HuffmanTree HT=HuffmanCoding(HC,w,code,codeLen);
     for(int r=0;r<codeLen;r++)cout<<"\n"<<code[r]<<"的字符的Huffman编码为："<<HC[r]<<endl;
     for(int i=0;i<aLen;i++){
        bool find=false;
        for(j=0;j<codeLen;j++){
           if(a[i]==code[j]){
               find=true;
               cout<<HC[j];
           }
        }
     
        if(!find)cout<<"空";
     }
}
*/
int main(int argc, char** argv) {
     MaxHeap maxHeap;
     int s,n,sel,Alen;
     char**codeA;
     int *IntA,*w;
     cout<<"input the number of the elements:";
     int len;
     cin>>len;
     int *a=new int[len];
     cout<<"input the element from 0 to "<<len<<endl;
     int temp;
     cin>>temp;
     for(int i=0;i<len;i++){
        int b=temp%10;
        temp=temp/10;
        a[i]=b;
     }
     maxHeap.Initialize(a,len);
     cout<<"大根堆操作："<<endl;
     cout<<"the sort of maxHeep:"<<endl;
     maxHeap.HeapSort(a,len);
     for(int h=0;h<len;h++)cout<<a[h]<<" "; 
     cout<<endl;
     cout<<"output the maxHeep(travel):"<<endl;
     Travel(maxHeap.root);
     cout<<endl; 
     cout<<"output the maxHeep（perOrder）"<<endl;
     preOrder(maxHeap.root);
     cout<<endl;
     cout<<"delete the max element"<<endl;
     maxHeap.DeleteMax(s);
     cout<<"output the maxHeep（perOrder）"<<endl;
     preOrder(maxHeap.root);
     cout<<endl;
     /*cout<<"Huffman操作"<<endl;
     cout<<"输入元素个数:"<<endl;
     cin>>Alen;
     IntA=new int[Alen];
     w=new int[Alen];
     for(n=0;n<Alen;n++){
        cout<<"输入第"<<n+1<<"个元素"<<endl;
        cin>>IntA[n];
        cout<<"\n输入对应权值\n";
        cin>>w[n];
     }
     HuffmanCoding(codeA,w,IntA,len);
     HTEcode(codeA,w,IntA,Alen,a,len);
     cout<<endl; */ 
     return 0;
}
