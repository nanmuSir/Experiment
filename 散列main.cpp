#ifndef _DICT     
#define _DICT  
#include<iostream>  
using namespace std;  
template<class E,class K> class SortedChain;  
template <class E ,class K>  
class SortedChainNode  
{  
friend class SortedChain<E,K>;  
private:  
K data;  
SortedChainNode<E,K> *link;  
};  
//E表示链表元素的数据类型, K是链表中排序所用到的关键字  
template<class E ,class K>  
class SortedChain  
{  
public:  
SortedChain() {first =0;}  
~SortedChain(){ }  
bool IsEmpty() const {return first ==0;}  
//int Length() const;  
bool Search(const K& k , E& e) const;  
SortedChain<E ,K>& Delete(const K& k , E& e);  
//SortedChain<E ,K>& Insert(const E& e);  
SortedChain<E ,K>& DistinctInsert(const E& e);  
void Output(ostream& out) const;  
private:  
SortedChainNode<E ,K> *first;  
};  
template<class E, class K>  
bool SortedChain<E,K>::Search(const K& k, E& e) const  
{// 搜索与k匹配的元素，结果放入e  
// 如果没有匹配的元素，则返回f a l s e  
SortedChainNode<E,K> *p =first;  
// 搜索与k相匹配的元素  
for (;p&& p->data < k;p = p->link);  
// 验证是否与k匹配  
if (p && p->data == k) // 与k相匹配  
{e = p->data; return true;}  
return false; // 不存在相匹配的元素  
}  
  
  
template<class E, class K>  
SortedChain<E,K>& SortedChain<E,K>  
::Delete(const K& k, E& e)  
{// 删除与k相匹配的元素  
// 并将被删除的元素放入e  
// 如果不存在匹配元素，则引发异常B a d I n p u t  
SortedChainNode<E,K> *p = first,  
*tp = 0; //跟踪p  
// 搜索与k相匹配的元素  
for (; p && p->data < k; tp = p,p = p->link;)  
  
  
// 验证是否与k匹配  
if (p && p->data == k) {// 找到一个相匹配的元素  
e = p->data; // 保存d a t a域  
// 从链表中删除p所指向的元素  
if (tp) tp->link = p->link;  
else first = p->link; // p是链首节点  
delete p;  
}  
  
  
return *this;  
  
  
}  
  
  
template<class E, class K>  
SortedChain<E,K>& SortedChain<E,K>::DistinctInsert(const E& e)  
{// 如果表中不存在关键值与e相同的元素，则插入e  
  
  
SortedChainNode<E,K> *p = first, *tp = 0; // 跟踪p  
// 移动tp 以便把e 插入到t p之后  
for (; p && p->data < e; tp = p, p = p->link);  
// 检查关键值是否重复  
//if (p && p->data == e)  return NULL;  
// 若没有出现重复关键值, 则产生一个关键值为e的新节点  
SortedChainNode<E,K> *q = new SortedChainNode<E,K>;  
q->data = e;  
// 将新节点插入到t p之后  
q->link = p;  
if (tp) tp->link = q;  
else first = q;  
return *this;  
}  
  
  
template<class E, class K>  
void SortedChain<E,K>::Output(ostream& out) const    
{// 将链表元素送至输出流     
SortedChainNode<E,K> *current;    
for (current=first; current; current = current->link)    
out<<current->data<<" ";    
}    
  
  
//重载<<     
template<class E, class K>  
ostream& operator<<(ostream& out, const SortedChain<E,K>& x)    
{    
    x.Output(out);     
    return out;    
}    
  
  
#endif  
  
  
#include<iostream>  
#include"dict"  
using namespace std;  
int main()  
{  
    SortedChain<int ,int> myChain;  
    myChain.DistinctInsert(10).DistinctInsert(20).DistinctInsert(3);  
    cout<<myChain<<endl;  
    return 0;  
} 
