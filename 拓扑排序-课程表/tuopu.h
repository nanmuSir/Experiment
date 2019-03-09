#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include<fstream>

using namespace std;

#define null 0
#define max_course_num  100  //最大课程总数  
class cid{
	char c[3];
};//课程号 

typedef struct Course{
	cid id[3];//课程号 
	char name[20];//课程名 
	
}Course; //课程

typedef struct PreCourse{
	int a;//课程在数组中的下标 
	struct PreCourse *nextarc;//指向下一先修的课程节点 
}PreCourse; //先修课 

typedef struct{
	Course course; 
	PreCourse *firstarc;// 指向第一条依附该顶点的弧的指针 
}CourseNode;//课程节点 

typedef struct{
	CourseNode courses[max_course_num];//邻接表 
	int xqs;
	int num;
}AlGraph;//课程有向图 

typedef struct{
	int data[max_course_num];
	int f,r;
}queue;//队列 

int whethercricle=0;//环数
int jxq;
//队列 
class Queue{
	public:
		void queue_init(queue *q);
		void queue_in(queue *q,int x);
		int queue_out(queue *q);
		int queue_empty(queue *q);
}Queue;
void Queue::queue_init(queue *q){//队初始化 
	q->f=q->r=0;
}
void Queue::queue_in(queue *q,int x){//入队 
	if((q->r+1)%max_course_num==q->f){
		cout<<"队满\t"<<endl;
		exit(0);
	}
	q->r=(q->r+1)%max_course_num;
	q->data[q->r]=x;
} 
int Queue::queue_out(queue *q){//出队 
	if(q->f==q->r){
		cout<<"队空\t"<<endl;
		exit(0);
	}
	q->f=(q->f+1)%max_course_num;
	return q->data[q->f];
}
int Queue::queue_empty(queue *q){//队列空 
	if(q->f==q->r)return 1;
	else return 0;
}
//图 
class Graph{
	public:
		AlGraph input();
		void output(AlGraph CGraph);
		void creatpre(AlGraph *CGraph);
}Graph;
void Graph::creatpre(AlGraph *CGraph){//先修关系
    system("cls");
	int choice;
	int i,n;
	int j;
	PreCourse *p,*q;
	cout<<endl<<"输入课程号的编号：\t"<<endl;
	for(i=0;i<CGraph->num;i++){
		if(i%4==0)cout<<endl;
		cout<<"("<<i+1<<")";//输入课程的编号 
		printf("%s\t",CGraph->courses[i].course.id);	
	} 
	cout<<endl;
	cout<<"\n输入每门课程先修课程号的编号（输入0表示没有或者结束）：\t"<<endl;
	for(i=0;i<CGraph->num;i++){
		printf("%s的先修课程：",CGraph->courses[i].course.id);
		cin>>j;
		n=0;
		while(j){//判断输入课程编号是否正确 
		    while(j<1||j>CGraph->num||j==i+1){
		    	if(j==i+1)cout<<"先修课程号有误\n";
				else cout<<"输入的先修课程号不在课程计划中"<<endl;
				cout<<"请重新输入：";
				cin>>j;
		    }
			p=(PreCourse *)malloc(sizeof(PreCourse));//malloc是动态随机分配内存空间的方法。
                                                    //可以根据需要分配内存空间给程序使用
                                                   //(char*)malloc(sizeof(char)*20)的意思是，动态分配空间为20个char型数据大小的空间。
                                                  //并且将返回的指针类型强制转换成char型指针。
			p->a=j-1;                                
			p->nextarc=null;                         
			if(n==0){
				CGraph->courses[i].firstarc=p;
				q=CGraph->courses[i].firstarc;
				n++;
			}
			else{
				q->nextarc=p;
				q=p;
				n++;
			}	
	        cin>>j;	
		}
	}
	system("pause");
	cout<<"(1)重新建立先修关系\t"<<"(2)确定\n";
	cout<<"请选择：";
	cin>>choice;
	if(choice==1)creatpre(CGraph);
	jxq=0; 
}
//输入 
AlGraph Graph::input(){//输入并建立课程图 
	AlGraph CGraph;
	int xqzs=0,kczs=0;//xqzs为总学期数，kczx为总课程数 
	int i;
	int choice;
	cout<<"教学计划:\n"<<endl;
	cout<<"(1).学期总数：\n";
	cin>>xqzs;
	CGraph.xqs=xqzs;
	cout<<"(2).共开设课程数：\n";
	cin>>kczs;
	CGraph.num=kczs;
	cout<<"(3).每门课课程号和课程名：\n"<<endl;
	for(i=0;i<kczs;i++){//输入课程号，课程名，学分 
		cout<<"课程号：";
		scanf("%s",CGraph.courses[i].course.id);
		cout<<"课程名：";
		scanf("%s",CGraph.courses[i].course.name);
		cout<<endl;
		CGraph.courses[i].firstarc=null;
	}
	cout<<"1.重新输入\t"<<"2.确定"<<endl;
	cout<<"请选择：";
	cin>>choice;
	if(choice==1){
		system("cls");
		input();
	}
	else{
		creatpre(&CGraph);//建立先修关系
		return CGraph; 
	}
}
//输出 
void Graph::output(AlGraph CGraph){//输出先修关系 
	int i,j,n;
	PreCourse *p;
	cout<<"课程编号\t"<<"课程名称\t"<<"先修课"<<endl;
	for(i=0;i<CGraph.num;i++){
		printf("%s\t\t%s\t\t",CGraph.courses[i].course.id,CGraph.courses[i].course.name);
		j=0;
		p=CGraph.courses[i].firstarc;
		while(p){
			n=p->a;
			printf(" %s  ",CGraph.courses[n].course.id);
			p=p->nextarc;
			j++;
		}
		if(j==0)cout<<"无";
		cout<<endl;
	} 
	system("pause");
} 
//判断 
class Judgement{  //判断类 
	public:
		void findindegree(AlGraph *CGraph,int indegree[]);
		void judgingcricle(AlGraph *CGraph,queue *q2);
}Judgement;

//
void Judgement::findindegree(AlGraph *CGraph,int indegree[]){
	int i;
	PreCourse *p;
	for(i=0;i<CGraph->num;i++){
		indegree[i]=0;
		p=CGraph->courses[i].firstarc;
		while(p){
			indegree[i]++;
			p=p->nextarc;
		}
	}
}
void Judgement::judgingcricle(AlGraph *CGraph,queue *q2){//判断是否有环和课程入队 
	int indegree[max_course_num];//入度
	int i,m,j,pd=0;
	float xf=0;
	PreCourse *p;
	queue q;
    Queue.queue_init(&q);//队初始化 
	findindegree(CGraph,indegree);//找入度
	for(i=0;i<CGraph->num;i++){
	    if(indegree[i]==0){
		   Queue.queue_in(&q,i);              //入度为0的点入栈 
		   indegree[i]--;
	    } 
    }
    m=0;
    Queue.queue_in(&q,-1);//-1入队判断
	jxq++;
	while(1){                                          
		i=Queue.queue_out(&q);             //若栈非空，取出栈顶顶点a，输出该顶点值 
		Queue.queue_in(q2,i);
		if(i!=-1){                         //删去该顶点 
			m++; 
			for(j=0;j<CGraph->num;j++)     //删去所有a的出边
			if(j!=i){
				if(indegree[j]==0){          
					Queue.queue_in(&q,j);
					indegree[j]--;
				}
				else{                            
					p=CGraph->courses[j].firstarc;
					while(p){
						if(p->a==i){
							indegree[j]--;
							if(indegree[j]==0){         //若边的另一顶点入度为0，则入栈
								Queue.queue_in(&q,j);
								indegree[j]--;
								pd=1;
							}
						}
						p=p->nextarc;
					} 
				}
			}
		}
		else{
			if(pd){
				pd=0;
				Queue.queue_in(&q,-1);
				jxq++;
			}
			else break;
		}
	} 
	if(m<CGraph->num){            //若图中仍有顶点，则图中有环 
		cout<<"课程先修课中存在循环，课程安排失败！"<<endl;
		whethercricle=1;
	}
	Queue.queue_in(q2,-1);
}
//排课方案 
class Edit{
	public:
		void layout1(AlGraph *CGraph,queue *q);
}Edit;

//输出函数 
void Edit::layout(AlGraph*CGraph,queue *q){
	FILE *bp;
	bp=fopen("courseplan.txt","w");
	int i,j,k,xq=1,ck[20];
	float xf;
	float m=CGraph->num/CGraph->xqs*1.0f;
	queue q1=*q;
	int n;
	int x;
	n=0;
	ck[0]=-1;
	for(i=0;i<20;i++){
		j=Queue.queue_out(&q1);
		ck[i]=j;
		if(j==-1)i--;
		if((Queue.queue_empty(&q1)))break;
	}
	cout<<"\n课程安排为："<<endl;
	fprintf(bp,"%s","\n课程安排为：\n");
	for(x=0;x<CGraph->xqs;x++){
		if(ck[0]!=-1){
			fprintf(bp,"%s","\n第");
	        fprintf(bp,"%d",xq);
	        fprintf(bp,"%s","学期课程安排为：\n") ;
			cout<<"\n第"<<xq++<<"学期课程安排为：\n";
			for(i=0;i<m;i++){
				k=ck[n];
				printf("%s  ",CGraph->courses[k].course.name);
				fprintf(bp," %s  ",CGraph->courses[k].course.name);
				n++;
			}
		}
	}
}
