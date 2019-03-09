
#include <iostream>

using namespace std;

template<class T>

struct Node//节点定义 

{

  T data;

  Node<T> *next;

};

template<class T>

class LinkList  //创建链表类 

{

  Node<T> *head;

  public:

  LinkList();

  LinkList(T a[], int n);

  ~LinkList();  //析构方法 

  int ListLength();

  T Get(int pos);

  int Locate(T item);

  void PrintLinkList();

  void Insert(int i, T item);

  T Delete(int i);

  void Invert();

  void Merge(LinkList<T> &L1,LinkList<T> &L2);

};

template<class T>

LinkList<T>::LinkList() 

{  //构造函数 

  head=new Node<T>;

  head->next=NULL;

}

template<class T>

LinkList<T>::LinkList(T a[], int n)

{  //构造函数（第二个链表） 

  Node<T> *s, *r;

  head=new Node<T>;

  r=head;

  for(int i=0; i<n; i++)

  {

    s=new Node<T>;

    s->data=a[i];

    r->next=s;

    r=s;

  }

  r->next=NULL;

}

template<class T>

int LinkList<T>::ListLength()
{  //得到链表长度 
  Node<T> *p;

  int num = 0;

  p = head -> next;

  while(p)
  {
    p = p-> next;
    num++;
  }
  return num;
}

template<class T>

T LinkList<T>::Get(int pos)

{  //得到元素所在位置 

  Node<T> *p;

  p = head -> next;

  int j=1;

  while(p && j<pos)

  {

    p=p->next;

    j++;

  }

  if(!p) {cerr<<"查找位置非法";exit(1);}

  else return p->data;

}

template<class T>

int LinkList<T>::Locate(T item)

{  //得到该位置的元素 

  Node<T> *p;

  p=head->next;

  int j=1;

  while(p && p->data!=item)

  {

    p=p->next;

    j++;

  }

  if(p) return j;

  else return 0;

}

template<class T>

void LinkList<T>::PrintLinkList()
{  //打印元素 
  Node<T> *p;
  p=head->next;
  while(p)
  {
    cout<<p->data<<"  ";
    p=p->next;
  }
  cout<<endl;
}

template<class T>
void LinkList<T>::Insert(int i, T item)
{   //插入元素 
  Node<T> *p,*s;

  p=head;

  int j=0;

  while(p && j < i-1)

  {

    p=p -> next;

    j++;

  }

  if(!p) {cerr<<"插入位置非法"; exit(1);}

  else {

    s=new Node<T>;

    s->data=item;

    s->next=p->next;

    p->next=s;

  }

}

template<class T>

T LinkList<T>::Delete(int i)
{  //删除元素 
  Node<T> *p,*q;
  T x;
  p=head;
  int j=0;
  while(p && j<i-1)
  {
    p=p->next;

    j++;

  }

  if(!p || !p->next) {cerr<<"删除位置非法";exit(1);}

  else

  {

    q=p->next;

    x=q->data;

    p->next=q->next;

    delete q;

    return x;

  }

} 

template<class T>

LinkList<T>::~LinkList()

{  //析构函数，析构链表LinkList 

  Node<T> *p,*q;

  p=head;

  while(p)

  {

    q=p;

    p=p->next;

    delete q;

  }

  head=NULL;

}

template<class T>

void LinkList<T>::Invert()

{  //将链表元素反序 

Node<T> *p,*q;

p=head->next;

head->next=NULL;

while(p!=NULL)

{

q=p;

p=p->next;

q->next=head->next;

head->next=q;

}

}

template<class T>

void LinkList<T>::Merge(LinkList<T> &L1,LinkList<T> &L2)

{  //合并两个链表的元素 

Node<T> *p1,*p2,*p3;

p1=L1.head->next;

p2=L2.head->next;

p3=L1.head;

while((p1!=NULL)&&(p2!=NULL))

{

if((p1->data)<(p2->data))

{

p3->next=p1;

p1=p1->next;

p3=p3->next;

}

else

{

p3->next=p2;

p2=p2->next;

p3=p3->next;

}

}

if(p1!=NULL) p3->next=p1;

if(p2!=NULL) p3->next=p2;

delete L2.head;//合并完成后，删除第二个链表 

L2.head=NULL;

}

int main()

{

int a[]={1,2,5,7,8,9,6};;

int b[]={9,8,6,5,2,7,3}; 
LinkList<int> c(a,7);
cout<<"单链表元素是："<<endl;
c.PrintLinkList();
cout<<"单链表的长度是："<<c.ListLength()<<endl;
int k;
bool f=true;
while(f)
{
cout<<"请选择想要进行的操作："<<endl;
cout<<"1.插入元素  2.删除元素  3.搜索指定元素  \n4.搜索指定位置元素  5.反序输出  6.链表合并  7.退出"<<endl;
cin>>k;
int m,p;
switch(k)
   {
	case 1:
		cout<<"想要插入的位置及元素？"<<endl;
		cin>>m;
		cin>>p;
		cout<<"在第"<<m<<"个位置插入值为"<<p<<"的元素："<<endl;
        c.Insert(m,p);
        c.PrintLinkList();
        break;
    case 2:
    	cout<<"想要删除删除第几位元素？"<<endl;
    	int o;
		cin>>o; 
		cout<<"删除顺序表的第"<<o<<"个元素："<<endl;
        c.Delete(o);
    	c.PrintLinkList();
    	break;
    case 3:
    	cout<<"想要搜索什么元素？"<<endl;
    	int i;
    	cin>>i;
    	cout<<"单链表的元素为"<<i<<"的是第"<<c.Locate(i)<<"个元素"<<endl;
    	break;
    case 4:
    	cout<<"想要搜索哪个位置的元素？"<<endl;
    	int u;
    	cin>>u;
        cout<<"单链表的第"<<u<<"个元素是："<<c.Get(u)<<endl;
        break;
    case 5:
    	c.Invert();
        cout<<"反序后的元素是："<<endl;
        c.PrintLinkList();
        break;
    case 6: 
        LinkList<int> d(b,7);
        cout<<"第二个链表元素是："<<endl;
        d.PrintLinkList();
        c.Merge(c,d);
        cout<<"合并后的元素是："<<endl;
        c.PrintLinkList();
        break;
    Default:
	    f=false;
	    break;
    }
}
}
