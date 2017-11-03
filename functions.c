#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myheader.h"

int opt1;
extern int c;
/*输出链表元素*/
void printstu(FILE *stream, stu* a)
{
	if (stream == stdout) printf("\n");
	fprintf(stream, "序号：%c\n姓名：%s\n学号：%s\n性别：%c\n", a->no, a->name, a->id_num, a->gender);
	fprintf(stream, "语文成绩：%d\n数学成绩：%d\n英语成绩：%d\n平均成绩：%.1f\n", a->grade_chi, a->grade_mat, a->grade_eng, a->grade_avg);
	if (stream == stdout) printf("\n");
}

/* 手动 创建链表或在链表末端添加元素，使用前需先创建一个元素*/
stu* create(stu* new)//创建链表的函数，可从文件中读取，也可手动输入
{
	puts("请输入学生姓名："), scanf("%s", new->name);
	puts("请输入学生学号："), scanf("%s", new->id_num);		
	puts("请输入学生性别，m表示男，w表示女："), scanf("\n%c", &new->gender);
	puts("请分别输入学生语数外成绩，中间用空格隔开："), scanf("%d %d %d", &new->grade_chi, &new->grade_mat, &new->grade_eng);
	new->no++;
	new->prev_stu = NULL;
	new->next_stu = NULL;
	new->grade_avg = .0;

	c = 1;//成功创建
	printf("创建节点成功！请输入对应数字选择下一步操作：1.继续创建；2.预览当前学生的数据；3.完成创建（默认）");
	scanf("%d", &opt1);
	printf("\n");
	if (opt1 == 1) 
	{
		stu *next = malloc(sizeof(stu));//创建下个节点
		next->prev_stu = new, new->next_stu = next;//下个节点连上上个节点，上个节点连上下个节点
		create(next); //继续创建
	}
	else if (opt1 == 2)
	{
		printstu(stdout, new);
		printf("请输入对应数字选择下一步操作：1.继续创建；2.完成创建（默认）");
		scanf("%d", &opt1);
		printf("\n");
		if (opt1 == 1) 
		{
			stu *next = malloc(sizeof(stu));//创建下个节点
			next->prev_stu = new, new->next_stu = next;//下个节点连上上个节点，上个节点连上下个节点
			create(next);//继续创建
		}
		else return new;
	}
	else return new;
}

/*从文件中读取新链表,使用前需先创建第一个元素*/
stu* read(FILE *in, stu *new) 
{
	int r1, r2, r3, r4;
	r1 = r2 = r3 = r4 = 0;
	if (r1 = fscanf(in, "%s[^\n]", new->name) != EOF)//文件没有读取完毕
	{
		if ((r1 != 1) ||
			(r2 = fscanf(in, "%s[^\n]", new->id_num) != 1) ||
			(r3 = fscanf(in, "\n%c", &new->gender) != 1) ||
			(r4 = fscanf(in, "%d %d %d %f", &new->grade_chi, &new->grade_mat, &new->grade_eng, &new->grade_avg) < 3))//任意字段读取出错
		{
			puts("有字段读取错误！请检查读取的文件！");
			if (c != 0)//有读取成功的节点
			{
				stu *last = new->prev_stu;//存储最后一个创建成功的节点
				free(new);//清除读取错误的节点
				return last;//返回最后一个创建成功的节点，退出函数
			}
			else
			{
				free(new);
				return NULL;
			}
		}
	}
	else
	{
		puts("读取完成！");
		stu *last = new->prev_stu;
		free(new);
		return last;
	}
	if(c == 0) new->prev_stu = NULL;
	new->next_stu = NULL;
	new->grade_avg = .0;
	new->no++;
	c = 1;
	stu *next = malloc(sizeof(stu));//下个节点
	next->prev_stu = new, new->next_stu = next;//下个节点连上上个节点，上个节点连上下个节点

	stu *final = read(in, next);
	return final;
}

/*释放之前分配的所有堆存储空间*/
void release(stu* a,stu* z)
{
	stu *b = a->next_stu;//先存储a的下一个节点，防止直接清除a后找不到下一个
	free(a);//清除a的所有节点
	if (b != z) release(b,z);//如果下一个节点不是第一个节点（没有清除完），就对下一个节点调用release，直到下一个为空（因为最后一个节点指向第一个，但第一个早被清掉了）
}

/*输出整个链表*/
void printList(FILE *stream, int printopt, stu* first1, stu* first2)//printopt为0时表示无格式输出，为1时表示带格式输出
{
	stu *current = first1;
	if (printopt == 1) printstu(stream, current);//选项为1则带格式输出
	else printforR(stream, current);//选项为2则无格式输出
	if (current->next_stu != first2)
	{
		current = current->next_stu;//处理下一个节点
		printList(stream, printopt, current, first2);
	}
}

/*无格式输出到文件以便下次读取使用*/
void printforR(FILE *stream, stu* a)
{
	fprintf(stream, "%s\n%s\n%c\n", a->name, a->id_num, a->gender);
	fprintf(stream, "%d %d %d %.1f\n", a->grade_chi, a->grade_mat, a->grade_eng, a->grade_avg);
}

/*计算每个学生的平均成绩*/
void average(stu *a, stu* first)
{
	a->grade_avg = (a->grade_chi + a->grade_mat + a->grade_eng) / 3.0;
	if (a->next_stu != first)
	{
		a = a->next_stu;
		average(a, first);
	}
}

/*根据输入的关键字查找节点*/
void search(key *k, stu *first)
{
	stu *current = first;
	switch (k->t)
	{
	case NO://按序号查找
		while (current->no != first->no)//没有从头查找一遍时
		{
			if (current->no == k->k.gender) printstu(stdout, current);//当输入的序号等于节点序号时输出该节点
			current = current->next_stu;//处理下一个节点
		}
		break;
	case NAME://按序号查找
		while (current->name != first->name)//没有从头查找一遍时
		{
			if (!strcmp(current->name,k->k.strings)) printstu(stdout, current);//当输入的姓名与节点姓名字段相同时输出该节点
			current = current->next_stu;//处理下一个节点
		}
		break;
	case ID://按序号查找
		while (current->id_num != first->id_num)//没有从头查找一遍时
		{
			if (!strcmp(current->id_num, k->k.strings)) printstu(stdout, current);//当输入的学号与节点学号字段相同时输出该节点
			current = current->next_stu;//处理下一个节点
		}
		break;
	case GENDER://按序号查找
		while (current->gender != first->gender)//没有从头查找一遍时
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//当输入的性别等于节点性别时输出该节点
			current = current->next_stu;//处理下一个节点
		}
		break;
	case CHI://按语文成绩查找
		while (current->gender != first->gender)//没有从头查找一遍时
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//当输入的性别等于节点性别时输出该节点
			current = current->next_stu;//处理下一个节点
		}
		break;
	case MAT://按序号查找
		while (current->gender != first->gender)//没有从头查找一遍时
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//当输入的性别等于节点性别时输出该节点
			current = current->next_stu;//处理下一个节点
		}
		break;
	case ENG://按序号查找
		while (current->gender != first->gender)//没有从头查找一遍时
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//当输入的性别等于节点性别时输出该节点
			current = current->next_stu;//处理下一个节点
		}
		break;
	case AVG://按序号查找
		while (current->gender != first->gender)//没有从头查找一遍时
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//当输入的性别等于节点性别时输出该节点
			current = current->next_stu;//处理下一个节点
		}
		break;
	}

}