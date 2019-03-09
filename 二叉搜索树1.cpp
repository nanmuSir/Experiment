//2、	接收键盘录入的二叉树前序序列和中序序列(各元素各不相同)，输出该二叉树的后序序列。
//*3、二叉搜索树的构造以及二叉搜索树输出。
#include<iostream>
using namespace std;

template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T> *leftChild,*rightChild;
	binaryTreeNode(){leftChild=rightChild=NULL;}
	binaryTreeNode(T theElement):element(theElement)
	{
		
		leftChild=rightChild=NULL;
	}
	binaryTreeNode(T theElement,binaryTreeNode *theLeftChild,binaryTreeNode *theRightChild):element(theElement)
	{
		
		leftChild=theLeftChild;
		rightChild=theRightChild;
	}
 };
template<class K,class E>
class binarySearchTree
{
	public:
	  binarySearchTree() {root = NULL; treeSize = 0;}
      bool empty()  {return treeSize == 0;}
      int size() {return treeSize;}
      pair<K, E>* find( K theKey);
      void insert( pair<K, E> thePair);
      void erase(K theKey);
      void inOrderOutput();
    private:
    	int treeSize;
    	binaryTreeNode<pair<K,E> > *root;   
    	void inOrder(binaryTreeNode<pair<K,E> >* t);
};
template<class K, class E>
 void binarySearchTree<K,E>::inOrderOutput()
 {
 	inOrder(root);
 }
 template<class K, class E>
 void binarySearchTree<K,E>::inOrder(binaryTreeNode<pair<K,E> >* t)
 {	// 中序遍历
   if (t != NULL)
   {
      inOrder(t->leftChild);
      cout<<t->element.first<<"  "<<t->element.second<<"      ";
      inOrder(t->rightChild);
   }
 }
template<class K, class E>
void binarySearchTree<K,E>::insert( pair<K, E> thePair)
{//插入thepair，如果存在与其关键字相同的数对，则覆盖 
   binaryTreeNode<pair<K, E> > *p = root,
                                *pp = NULL;
   while (p != NULL)
   {// 检查元素 p->element
      pp = p;
      // 移动p到它的一个孩子节点 
      if (thePair.first < p->element.first)
         p = p->leftChild;
      else
         if (thePair.first > p->element.first)
            p = p->rightChild;
         else
         {// 覆盖旧值 
            p->element.second = thePair.second;
            return;
         }
   }

   // 建立新节点，然后与pp相连 
   binaryTreeNode<pair<K, E> > *newNode
                 = new binaryTreeNode<pair<K, E> > (thePair);
   if (root != NULL) //如果数非空 
      if (thePair.first < pp->element.first)
         pp->leftChild = newNode;
      else
         pp->rightChild = newNode;
   else
      root = newNode; // 否则插入空树 
   treeSize++;
}

template<class K, class E>
void binarySearchTree<K,E>::erase(K theKey)
{// 删除关键字为thekey的数对 

   // 查找关键字为thekey的节点 
   binaryTreeNode<pair<K, E> > *p = root,
                                     *pp = NULL;
   while (p != NULL && p->element.first != theKey)
   {// 将p移动到它的一个孩子节点 
      pp = p;
      if (theKey < p->element.first)
         p = p->leftChild;
      else
         p = p->rightChild;
   }
   if (p == NULL)
      return; // 没有匹配数对则返回 


   // 当p有两个子树时 
   if (p->leftChild != NULL && p->rightChild != NULL)
   {// 在p的左子树中寻找最大元素 
      binaryTreeNode<pair<K, E> > *s = p->leftChild,
                                       *ps = p; //ps为p的父亲 
      while (s->rightChild != NULL)
      {// 移动到最大元素
         ps = s;
         s = s->rightChild;
      }

      // 将最大元素s移动到p
      binaryTreeNode<pair<K, E> > *q =
         new binaryTreeNode<pair<K, E> >
             (s->element, p->leftChild, p->rightChild);
      if (pp == NULL)
         root = q;
      else if (p == pp->leftChild)
              pp->leftChild = q;
           else
              pp->rightChild = q;
      if (ps == p) pp = q;
      else pp = ps;
      delete p;
      p = s;
   }

   // p最多只有一个孩子 
   // 把孩子指针存放入p 
   binaryTreeNode<pair<K, E> > *c;
   if (p->leftChild != NULL)
      c = p->leftChild;
   else
      c = p->rightChild;

  
   if (p == root)
      root = c;
   else
   {// 处理待释放的节点的父亲与子树 
      if (p == pp->leftChild)
         pp->leftChild = c;
      else pp->rightChild = c;
   }
   treeSize--;
   delete p;
}
int main()
{
	binarySearchTree<int,int> a;
	pair<int, int> p;
	int m,n,number;
	cout<<"请输入要输入的个数：";
	cin>>number;
	for(int i=0;i<number;i++)
	{
	  cout<<"请输入关键字：";
	  cin>>m;
	  cout<<"请输入值：";
	  cin>>n;
	  p.first=m;p.second=n;
	  a.insert(p);	
	}

	cout<<"a的节点数："<<a.size()<<endl;
	cout<<"a的后序输出："; 
	a.inOrderOutput();
    cout<<endl;
    int temp;
    cout<<"请输入你要删除的节点的关键字：";
    cin>>temp;
    a.erase(temp);
	cout<<"a的后序输出："; 
	a.inOrderOutput();
    cout<<endl;
    int mm,nn;
    cout<<"请输入想要插入的节点关键字:"<<endl; 
    cin>>mm;
    cout<<"请输入想要插入的节点值:"<<endl;
    cin>>nn;
    p.first=mm;p.second=nn;
	a.insert(p);
    cout<<"a的节点数："<<a.size()<<endl;
	cout<<"a的后序输出："; 
	a.inOrderOutput();
    cout<<endl;
	
	return 0;
}
