#include <iostream>

using namespace std;

template<class T>
class Term
{
    friend SparseMatrix<T>;
private:
    int row, column;
    T value;
};
template<class T>
void SparseMatrix<T>::Transpose(SparseMatrix<T>& b) const
{//对*this进行转置，转置后的矩阵存储在b中
    if (terms > b.MaxTerms) throw NoMem();

    b.rows = columns;
    b.columns = rows;
    b.terms = terms;

    int *ColSize, *RowNext;
    ColSize = new int[columns + 1];
    RowNext = new int[columns + 1];

    //计算每一列的元素数量
    for (int i = 1; i <= columns; i++)
        ColSize[i] = 0;
    for (int i = 0; i < terms; i++)
        ColSize[a[i].column]++;

    //计算每一行的开始位置
    RowNext[1] = 0;
    for (int i = 2; i <= columns; i++)
        RowNext[i] = RowNext[i - 1] + ColSize[i - 1];

    for (int i = 0; i < terms; i++) {
        int j = RowNext[a[i].column]; //b中a[i]的位置,a是Term的数组
        RowNext[a[i].column]++;
        b.a[j].column = a[i].row;
        b.a[j].row = a[i].column;
        b.a[j].value = a[i].value;
    }

    delete[] ColSize;
    delete[] RowNext;
}
template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T>& b, SparseMatrix<T>& c) const
{//将*this与b相加，得到的矩阵存在c中
    if (rows != b.rows || columns != b.columns)
        throw SizeMismatch();   //矩阵不兼容

    //设置矩阵c的特征
    c.rows = rows;
    c.columns = columns;
    c.terms = 0; //初始化项数

    //定义到*this和b的指针
    int ct = 0, cb = 0;

    //移动*this和b的指针
    while (ct < terms && cb < b.terms) {
        //计算项的行主索引值
        int it = a[ct].row * columns + a[ct].column;
        int ib = b.a[cb].row * columns + b.a[cb].column;

        if (it < ib) {
            c.Append(a[ct]);
            ct++;
        }
        else if (it == ib) {
            if (a[ct].value + b.a[cb].value) { 
                //如果相加不为0，则加到c后面
                Term<T> temp;
                temp.column = a[ct].column;
                temp.row = a[ct].row;
                temp.value = a[ct].value + b.a[cb].value;
                c.Append(temp);
            }
            ct++;
            cb++;
        }
        else {
            c.Append(b.a[cb]);
            cb++;
        }
    }

    for (; ct < terms; ct++)
        c.Append(a[ct]);
    for (; cb < b.terms; cb++)
        c.Append(b.a[cb]);
}
