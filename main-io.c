#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"

//错误：
//1.删除指定数据、按平均成绩排序尚未实现
int main()
{
	int opt;//存储选项
	extern int c;
	c = 0;//链表是否创建，0表示未创建，1表示已创建
	char fileinname[20], fileoutname[20];
	printf("\n");
	printf("欢迎来到学生管理系统。");
	while(1)//实现重复运行
	{
		printf("请输入选项对应的数字选择要进行的操作：\n1.创建链表\n2.打印链表\n3.删除链表\n");
		printf("4.插入数据\n5.删除数据\n6.计算平均成绩\n7.按平均成绩排序（降序）\n8.保存链表\n9.退出\n");
		printf("\n");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1://选择创建链表
			puts("请选择数据来源 1.手动输入；2.来自文件；3.回到上级。请输入选项对应的数字以选择：");
			scanf("%d", &opt);
			printf("\n");
			stu *first = malloc(sizeof(stu));//创建链表时用，是链表的第一个元素
			first->no = 0;//序号初始为0，后面会自动添加
			stu *last;//链表的最后一个元素
			stu *new = malloc(sizeof(stu));//插入数据时用
			//创建链表的选项
			switch (opt)
			{
			case 1://选择手动输入
				last = create(first);//调用手动创建链表的函数，并把创建的最后一个节点的地址赋给地址last
				last->next_stu = first, first->prev_stu = last;//首尾双向相连
				c = 1;//已经创建了一个链表
				break;
			case 2://选择来自文件
				printf("请输入存储数据的文件名（必须与程序位于同一目录）：");
				scanf("%s", fileinname);//读取存放数据的文件名
				printf("**********************************************************************\n");
				FILE *filein;
				if ((filein = fopen(fileinname, "r"))== 0) 
				{
					puts("读取文件失败，请检查文件！");//创建读取文件的数据流
					break;
				}
				last = read(filein, first);//调用创建链表的函数，返回最后一个节点
				if (last != NULL)
				{
					last->next_stu = first, first->prev_stu = last;//首尾双向相连
					c = 1;//已经创建了一个链表
				}
				break;
			}
			break;
		case 2://选择打印链表
			printList(stdout, 1, first, first);
			break;
		case 3://选择删除链表
			//如果创建了链表
			if (c == 1)
			{
				int nodes = 0;
				if (first == last) nodes = 1;//判断节点数，即是否只创建了一个元素
				release(first, last);
				if (nodes != 1) free(last);//如果只创建了一个元素要跳过这一步
				c = 0;
			}
			break;
		case 4://选择插入数据
			first->prev_stu->next_stu = new, new->next_stu = first;//原先的最后一个节点更新为新节点，新节点的后一个节点是第一个节点
			last = create(new);
			last->next_stu = first, first->prev_stu = last;//首尾双向相连
			break;
		case 6://选择计算平均成绩
			if (c == 0)puts("尚未创建链表，请先创建链表。");
			else average(first, first);
			break;
		case 8://选择保存链表
			printf("请为要保存链表的文件命名（文件将与程序储存在同一目录）：");
			scanf("%s", fileoutname);
			printf("\n");
			FILE *fileout = fopen(fileoutname, "w");
			printf("请选择保存选项：1.暂时保存（无格式，下次可读取）；2.最终版（带格式，下次不可读取）");
			scanf("%d", &opt);
			switch (opt)
			{
			case 1://选择无格式保存
				printList(fileout, 0, first, first);
				break;
			case 2://选择带格式保存
				printList(fileout, 1, first, first);
				break;
			}
			break;
		case 9://选择退出
			//如果创建了链表
			if (c == 1) 
			{
				release(first, last);
				free(last);
			}
			return 0;
		}
	}
}