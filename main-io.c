#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"

//错误：
//1.删除指定数据、按平均成绩排序尚未实现

//经验教训：
//1.设计函数时，要把函数接收什么参数、做什么、返回什么想清楚
//2.贯穿整个过程的变量要留心。
//3.每一块都要把算法设计清楚，即使是最简单的部分。
int main()
{
	char opt;//存储选项
	extern int c;
	c = 0;//链表节点个数,0表示未创建
	char fileinname[20], fileoutname[20];
	stu *x,*x2;//删除数据时用
	stu *prev, *next;//删除数据时用
	printf("欢迎来到学生管理系统。");
	while(1)//实现重复运行
	{
		fflush(stdin);
		printf("\n");
		printf("请输入选项对应的数字选择要进行的操作：\n1.创建链表\n2.打印链表\n3.删除链表\n");
		printf("4.插入数据\n5.删除数据\n6.计算平均成绩\n7.按平均成绩排序（降序）\n8.保存链表\n9.退出\n");
		printf("\n");
		scanf("\n%c", &opt);
		printf("\n");
		switch (opt)
		{
		case '1'://选择创建链表
			puts("请选择数据来源：1.手动输入；2.来自文件；3.回到上级。请输入选项对应的数字以选择：");
			scanf("\n%c", &opt);
			printf("\n");
			stu *first = malloc(sizeof(stu));//创建链表时用，是链表的第一个元素
			first->no = 0;//序号初始为0，后面会自动添加
			stu *last;//链表的最后一个元素

			//创建链表的选项
			switch (opt)
			{
			case '1'://选择手动输入
				printf("\n");
				last = create(first);//调用手动创建链表的函数，并把创建的最后一个节点的地址赋给地址last
				last->next_stu = first, first->prev_stu = last;//首尾双向相连
				c ++;//已经创建了一个链表
				break;
			case '2'://选择来自文件
				printf("\n");
				printf("请输入存储数据的文件名（必须与程序位于同一目录）：");
				scanf("%s", fileinname);//读取存放数据的文件名
				printf("\n");
				FILE *filein;
				if ((filein = fopen(fileinname, "r"))== 0) 
				{
					puts("读取文件失败，请检查文件！");//创建读取文件的数据流
					break;
				}
				last = read(filein, first);//调用创建链表的函数，返回最后一个节点
				if (last != NULL) last->next_stu = first, first->prev_stu = last;//首尾双向相连
				break;
			}
			break;
		case '2'://选择打印链表
			if (c != 0) printList(stdout, 1, first, first);
			else printf("请先创建链表！\n");
			break;
		case '3'://选择删除链表
			//如果创建了链表
			if (c != 0)
			{
				release(first, last);
				if (c != 1) free(last);//如果只创建了一个元素要跳过这一步
				c = 0;
			}
			else printf("请先创建链表！\n");
			break;
		case '4'://选择插入数据
			if (c == 0)
			{
				printf("请先创建链表！\n");
				break;
			}
			last->next_stu = malloc(sizeof(stu));//创建下一个新的节点
			last->next_stu->prev_stu = last;//末两个先前后相连
			last = create(last->next_stu);
			last->next_stu = first, first->prev_stu = last;//首尾双向相连
			last->no = last->prev_stu->no + 1;
			break;
		case '5'://选择删除数据
			if (c == 0)
			{
				printf("请先创建链表！\n");
				break;
			}
			x = first;
			puts("需要搜索链表以定位待删除数据吗？(y/n)");
			scanf("\n%c", &opt);
			printf("\n");
			if (opt == 'y') search(first);
			puts("请输入要删除节点的序号：");
			scanf("\n%c", &opt);
			printf("\n");
		//删除指定序号的数据
			if (opt == '1')//删除第一条
			{
				if (first == next)//链表只有一个节点
				{
					release(first, last);
					printf("链表已为空，请重新创建链表！\n");
					break;
				}
				else
				{
					next = first->next_stu;
					free(first);
					first = next;
					first->prev_stu = last, last->next_stu = first;
					x = first;
					c--;
					printf("删除成功！\n");
				}
			}
			else if (opt - '0' == last->no)//删除最后一条
			{
				prev = last->prev_stu;
				free(last);
				last = prev;
				last->next_stu = first; first->prev_stu = last;
				c--;
				printf("删除成功！\n");
			}
			else do
			{
				if (x->no  == opt - '0') 
				{
					prev = x->prev_stu, next = x->next_stu;
					x2 = x->next_stu;//提前把x的下个节点存下来，防止x被释放后找不到x的下个地址
					free(x);
					x = x2;//续上
					c--;
					printf("删除成功！\n");
					prev->next_stu = next, next->prev_stu = prev;
				}
				else x = x->next_stu;//处理下一个节点
			} while (x != first);//没有从头查找一遍时
			if (c != 0)//重新给序号
			{
				x = x->prev_stu;
				do
				{
					x->no = c--;
					x = x->prev_stu;//处理下一个节点
				} while (x != last);//没有从头一遍时
				c = x->no;//重新取回链表节点个数
			}
			else printf("链表已为空，请重新创建链表！\n");
			break;
		case '6'://选择计算平均成绩
			if (c == 0)printf("尚未创建链表，请先创建链表。\n");
			else average(first, first);
			break;
		case '7'://选择按平均成绩排序（降序）
			if (c <= 1)printf("不满足排序条件，请检查链表。\n");
			else
			{
				stu *max = malloc(sizeof(stu));//创建新链表
				*max = *first;//新链表第一项设为旧链表第一项
				max->prev_stu = max, max->next_stu = max;//新链表双向闭环
				if (max->grade_avg <= 0.09f)
				{
					printf("请先计算平均成绩！\n");
					break;
				}
				else max = sorting(first, max, first->next_stu);
				printf("排序完成，结果如下：\n");
				printList(stdout, 1, max, max);
				puts("排序结果不会保存在程序中。需要把排序结果保存为文件吗？(y/n)");
				scanf("\n%c", &opt);
				printf("\n");
				if (opt == 'y')
				{
					printf("请为要保存链表的文件命名（文件将与程序储存在同一目录）：");
					scanf("%s", fileoutname);
					printf("\n");
					FILE *fileout = fopen(fileoutname, "w");
					printf("请选择保存选项：1.暂时保存（无格式，可读取）；2.最终版（带格式，不可读取）");
					scanf("\n%c", &opt);
					printf("\n");
					switch (opt)
					{
					case '1'://选择无格式保存
						printList(fileout, 0, max, max);
						printf("保存成功！\n");
						break;
					case '2'://选择带格式保存
						printList(fileout, 1, max, max);
						printf("保存成功！\n");
						break;
					}
				}
				release(max, max->prev_stu);
			}
			break;
		case '8'://选择保存链表
			if (c == 0)
			{
				printf("请先创建链表！\n");
				break;
			}
			printf("请为要保存链表的文件命名（文件将与程序储存在同一目录）：");
			scanf("%s", fileoutname);
			printf("\n");
			FILE *fileout = fopen(fileoutname, "w");
			printf("请选择保存选项：1.暂时保存（无格式，可读取）；2.最终版（带格式，不可读取）");
			scanf("\n%c", &opt);
			switch (opt)
			{
			case '1'://选择无格式保存
				printList(fileout, 0, first, first);
				printf("保存成功！\n");
				break;
			case '2'://选择带格式保存
				printList(fileout, 1, first, first);
				printf("保存成功！\n");
				break;
			}
			break;
		case '9'://选择退出
			//如果创建了链表
			if (c != 0) 
			{
				release(first, last);
				free(last);
			}
			return 0;
		}
	}
}