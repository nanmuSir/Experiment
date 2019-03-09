#include<iostream>
using std::cout;
using std::cin;
using std::endl;

const int MAX = 10;

template<class T>
void Subset(T list[],bool exists[], int k, int m)
{//list 全集，exists 判断是否存在于子集内，k 递归层数，m 递归终点
    if(k == m-1) {
        //当达到终点时输出，按照exists[i]是否为0判断是否在集合内
        int i = 0;
        exists[k] = 0;
        for(i=0; i<m-1; i++)
            if(exists[i]) cout << list[i] << ' ';
        if(exists[i]) cout << list[i];
        cout << endl;
        exists[k] = 1;
        for(i=0; i<m-1; i++)
            if(exists[i]) cout << list[i] << ' ';
        if(exists[i]) cout << list[i] << endl;
        return;
    }
    exists[k] = 0;//定义list[k]不在子集内
    Subset(list,exists,k+1,m);
    exists[k] = 1;//定义list[k]在子集内
    Subset(list,exists,k+1,m);
}

int main()
{
    char ch[MAX];
    bool exists[MAX] = {0};
    int i = 0;
    while(i<MAX){
        cin.get(ch[i]);
        if(ch[i] == ' ' || ch[i] == '\n')
            break;
        i++;
    }
    Subset(ch,exists,0,i);
}
