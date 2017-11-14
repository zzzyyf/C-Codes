#pragma warning(disable:4996)
#include <stdio.h>
typedef struct stu
{
	struct stu *prev_stu;//上一个学生
	struct stu *next_stu;//下一个学生
	int no;//序号
	char name[20];//姓名
	char id_num[20];//学号
	char gender;//性别，m=男，w=女
	int grade_chi;//语文成绩
	int grade_mat;//数学成绩
	int grade_eng;//英语成绩
	float grade_avg;//平均成绩
}stu;

union keyword//存储搜索时使用的关键字
{
	char strings[20];//姓名和学号
	char gender;//性别和序号
	int grades;//语数外成绩
	float average;//平均成绩
};

enum type { NO, NAME, ID, GENDER, CHI, MAT, ENG, AVG };//关键字的类型

typedef struct//关键字的内容和类型
{
	union keyword k;//输入的关键字
	enum type t;//关键字类型
}searchkey;

int c;//是否创建链表

/*输出链表元素*/
void printstu(FILE *stream, stu* a);

/*创建链表或在链表末端添加元素，使用前需先创建一个元素*/
stu* create(stu* new);//手动创建链表的函数

/*从文件中读取新链表，返回创建成功的最后一个节点使用前需先创建第一个元素*/
stu* read(FILE *in, stu *new);

/*释放之前分配的所有堆存储空间*/
void release(stu* a, stu* z);

/*输出整个链表*/
void printList(FILE *stream,int printopt, stu* first1, stu* first2);//printopt为0时表示无格式输出，为1时表示带格式输出

/*无格式输出到文件以便下次读取使用*/
void printforR(FILE *stream, stu* a);

/*计算每个学生的平均成绩*/
void average(stu *a, stu* first);

/*根据输入的关键字查找节点*/
void search(stu *first);

/*对链表的节点按照平均成绩降序排序*/
stu *sorting(stu *first, stu *max, stu *old);