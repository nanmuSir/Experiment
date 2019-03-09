#include <iostream>
#include <cstring>
#include<stdio.h>
#include <cmath>
#include <stdlib.h>
#include<windows.h>
//#include <queue>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

float f(float x, float y, float z) {  
    float a = x * x + 9.0f / 4.0f * y * y + z * z - 1;  
    return a * a * a - x * x * z * z * z - 9.0f / 80.0f * y * y * z * z * z;  
}  
  
float h(float x, float z) {  
    for (float y = 1.0f; y >= 0.0f; y -= 0.001f)  
        if (f(x, y, z) <= 0.0f)  
            return y;  
    return 0.0f;  
}  

int main() {
	cout<<"这是一份来自程序猿的女生节礼物\n"<<endl;
	Sleep (1500);
	cout<<"不过你要先回答一个问题才能收到礼物\n"<<endl;
	Sleep (1500);
	cout<<"那么，问题就是：\n"<<endl;
	Sleep (1500);
	cout<<"你是不是女汉子？(是 或 不是)\n"<<endl;
	string str;
	cin>>str;
	if(str=="是")cout<<"\n对不起，这份礼物只送给萌妹子~\n"<<endl;
	if(str=="不是")cout<<"\n对不起，这份礼物只送给女汉子~\n"<<endl;
	Sleep (4500);
	cout<<"哈哈哈逗你的！这份礼物可是专属于你一个人的！\n"<<endl;
	Sleep (2000);
	
/*	void color(short x) //自定义函根据参数改变颜色   
    {
    if(x>=0 && x<=15)//参数在0-15的范围颜色  
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //只有一个参数，改变字体颜色   
    else//默认的颜色白色  
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
    }
	//system("color 95");
*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);  
    printf("女  ");
    Sleep (1500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 | FOREGROUND_INTENSITY | 4 | BACKGROUND_INTENSITY);  
    printf("生  ");
    Sleep (1500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1 | FOREGROUND_INTENSITY | 13 | BACKGROUND_INTENSITY);  
    printf("节  ");
    Sleep (1500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6 | FOREGROUND_INTENSITY | 3 | BACKGROUND_INTENSITY);  
    printf("快  ");
    Sleep (1500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN| FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY);  
    printf("乐  ");
    Sleep (1500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | 5 | BACKGROUND_INTENSITY);  
    printf("！  \n\n\n");
    Sleep (1500);
   
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY);  
    printf("以后你可要小心点哦\n\n\n");
    Sleep (2500);
    cout<<"因为，我的心里住着一个强盗\n\n"<<endl;
    Sleep (2500);
    cout<<"随时可能把你绑走，送到我心里\n\n"<<endl;
	Sleep (2500);
	cout<<"那样，我就会爱上你\n\n"<<endl;
	Sleep (2500);
	  
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
    for (float z = 1.5f; z > -1.5f; z -= 0.05f) {  
        for (float x = -1.5f; x < 1.5f; x += 0.025f) {  
            float v = f(x, 0.0f, z);  
            if (v <= 0.0f) {  
                float y0 = h(x, z);  
                float ny = 0.01f;  
                float nx = h(x + ny, z) - y0;  
                float nz = h(x, z + ny) - y0;  
                float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);  
                float d = (nx + ny - nz) * nd * 0.5f + 0.5f;  
                putchar(".:-=+*#%@"[(int)(d * 5.0f)]);  
            }  
            else  
                putchar(' ');  
        }  
        putchar('\n');  
    }  
    system("pause");
	return 0;
}
