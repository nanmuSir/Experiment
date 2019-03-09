# include <iostream>
# include <stdio.h>
using namespace std;
void swap(int &a, int &b)
{
    //交换a和b
    int temp = a;
    a = b;
    b = temp;
}
void perm(int list[], int k, int m)
{
    if (k == m)//递归的基础部分
    {
        for (int i = 0; i <= m; i++)
        {
            cout << list[i];
        }
        cout << endl;
    }
    else
    {
        for (int i = k; i <= m; i++)
        {
            swap(list[k], list[i]);
            perm(list, k + 1, m);
            swap(list[k], list[i]);
        }
    }
}
int main()
{
    int list[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cout << "Please enter a number n in order to generate the full array from 1 to n (Not exceeding 9)." << endl;
    int n;
    cin >> n;
    while (n > 9 || n <1)
    {
        cout << "Out of range, please enter again." << endl;
        cin >> n;
    }
    perm(list, 0, n - 1);
    system("pause");
    return 0;
}
