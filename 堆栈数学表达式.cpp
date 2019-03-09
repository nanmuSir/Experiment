#include<iostream>  
#include<stack>  
#include<string>  
#include <stdlib.h>
using namespace std;  
int priority(int state,char a)  
{//计算操作符优先级的函数，注意state表示运算符状态：  
//state=1表示还未进栈，state=0表示栈内优先级，注意  
//这只对‘（’起作用  
    int result;  
    switch (a){  
    case '+':  
    case '-':  
        result = 1;  
        break;  
    case '*':  
    case '/':  
        result = 2;  
        break;  
    case '(':  
        if (state == 0)  
            result = 3;  
        else  
            result = 0;  
        break;  
    case '#':  
        result = 0;  
        break;  
    default:  
        break;  
    }  
    return result;  
}  
double calculate(char op, double op1, double op2)  
{  
    double result;  
    switch (op){  
    case '+':  
        result = op1 + op2;  
        break;  
    case '-':  
        result = op1 - op2;  
        break;  
    case '*':  
        result = op1*op2;  
        break;  
    case '/':  
        result = op1 / op2;  
        break;  
    default:  
        break;  
    }  
    return result;  
}  
int main()  
{  
    string s;  
    while (cin >> s){//测试多组数据  
        stack<char> operation;//存放操作符的栈  
        stack<double> operand;//存放操作数的栈  
        operation.push('#');//先将‘#’压栈  
        string num;//存放操作数  
        for (int i = 0; i < s.length(); i++){  
            if (isdigit(s[i])){//出现数字  
                while (isdigit(s[i]) || s[i] == '.'){//将操作数提取完全  
                    num.push_back(s[i]);  
                    i++;  
                }  
                double a = atof(num.c_str());//string->double  
                operand.push(a);//操作数入栈  
                num.clear();//num清空以备下次使用  
                i--;//位置还原  
            }  
            else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '('){//出现运算符  
                if (priority(0, s[i])>priority(1, operation.top()))//优先级比较  
                    operation.push(s[i]);//>,直接入栈  
                else{  
                    while (priority(0, s[i]) <= priority(1, operation.top())){//<,出栈并进行计算直至>  
                        char temp = operation.top();  
                        operation.pop();  
                        double op2 = operand.top();  
                        operand.pop();  
                        double op1 = operand.top();  
                        operand.pop();  
                        operand.push(calculate(temp, op1, op2));  
                    }  
                    operation.push(s[i]);//不要忘了最后操作符入栈  
                }  
            }  
            else if (s[i] == ')'){//扫描到‘）’  
                while (operation.top() != '('){//出栈直至‘（’  
                    char temp = operation.top();  
                    operation.pop();  
                    double op2 = operand.top();  
                    operand.pop();  
                    double op1 = operand.top();  
                    operand.pop();  
                    operand.push(calculate(temp, op1, op2));  
                }  
                operation.pop();//‘（’出栈  
            }  
            else{//非法字符的处理  
                cout << "error!" << endl;  
                return 0;  
            }  
        }  
        while (operation.top() != '#'){//扫尾工作  
            char temp = operation.top();  
            operation.pop();  
            double op2 = operand.top();  
            operand.pop();  
            double op1 = operand.top();  
            operand.pop();  
            operand.push(calculate(temp, op1, op2));  
        }  
        cout << operand.top() << endl;//输出结果  
    }  
    return 0;  
}
