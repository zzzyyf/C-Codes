#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"

//����
//1.ɾ��ָ�����ݡ���ƽ���ɼ�������δʵ��
int main()
{
	int opt;//�洢ѡ��
	extern int c;
	c = 0;//�����Ƿ񴴽���0��ʾδ������1��ʾ�Ѵ���
	char fileinname[20], fileoutname[20];
	printf("\n");
	printf("��ӭ����ѧ������ϵͳ��");
	while(1)//ʵ���ظ�����
	{
		printf("������ѡ���Ӧ������ѡ��Ҫ���еĲ�����\n1.��������\n2.��ӡ����\n3.ɾ������\n");
		printf("4.��������\n5.ɾ������\n6.����ƽ���ɼ�\n7.��ƽ���ɼ����򣨽���\n8.��������\n9.�˳�\n");
		printf("\n");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1://ѡ�񴴽�����
			puts("��ѡ��������Դ 1.�ֶ����룻2.�����ļ���3.�ص��ϼ���������ѡ���Ӧ��������ѡ��");
			scanf("%d", &opt);
			printf("\n");
			stu *first = malloc(sizeof(stu));//��������ʱ�ã�������ĵ�һ��Ԫ��
			first->no = 0;//��ų�ʼΪ0��������Զ����
			stu *last;//��������һ��Ԫ��
			stu *new = malloc(sizeof(stu));//��������ʱ��
			//���������ѡ��
			switch (opt)
			{
			case 1://ѡ���ֶ�����
				last = create(first);//�����ֶ���������ĺ��������Ѵ��������һ���ڵ�ĵ�ַ������ַlast
				last->next_stu = first, first->prev_stu = last;//��β˫������
				c = 1;//�Ѿ�������һ������
				break;
			case 2://ѡ�������ļ�
				printf("������洢���ݵ��ļ��������������λ��ͬһĿ¼����");
				scanf("%s", fileinname);//��ȡ������ݵ��ļ���
				printf("**********************************************************************\n");
				FILE *filein;
				if ((filein = fopen(fileinname, "r"))== 0) 
				{
					puts("��ȡ�ļ�ʧ�ܣ������ļ���");//������ȡ�ļ���������
					break;
				}
				last = read(filein, first);//���ô�������ĺ������������һ���ڵ�
				if (last != NULL)
				{
					last->next_stu = first, first->prev_stu = last;//��β˫������
					c = 1;//�Ѿ�������һ������
				}
				break;
			}
			break;
		case 2://ѡ���ӡ����
			printList(stdout, 1, first, first);
			break;
		case 3://ѡ��ɾ������
			//�������������
			if (c == 1)
			{
				int nodes = 0;
				if (first == last) nodes = 1;//�жϽڵ��������Ƿ�ֻ������һ��Ԫ��
				release(first, last);
				if (nodes != 1) free(last);//���ֻ������һ��Ԫ��Ҫ������һ��
				c = 0;
			}
			break;
		case 4://ѡ���������
			first->prev_stu->next_stu = new, new->next_stu = first;//ԭ�ȵ����һ���ڵ����Ϊ�½ڵ㣬�½ڵ�ĺ�һ���ڵ��ǵ�һ���ڵ�
			last = create(new);
			last->next_stu = first, first->prev_stu = last;//��β˫������
			break;
		case 6://ѡ�����ƽ���ɼ�
			if (c == 0)puts("��δ�����������ȴ�������");
			else average(first, first);
			break;
		case 8://ѡ�񱣴�����
			printf("��ΪҪ����������ļ��������ļ�������򴢴���ͬһĿ¼����");
			scanf("%s", fileoutname);
			printf("\n");
			FILE *fileout = fopen(fileoutname, "w");
			printf("��ѡ�񱣴�ѡ�1.��ʱ���棨�޸�ʽ���´οɶ�ȡ����2.���հ棨����ʽ���´β��ɶ�ȡ��");
			scanf("%d", &opt);
			switch (opt)
			{
			case 1://ѡ���޸�ʽ����
				printList(fileout, 0, first, first);
				break;
			case 2://ѡ�����ʽ����
				printList(fileout, 1, first, first);
				break;
			}
			break;
		case 9://ѡ���˳�
			//�������������
			if (c == 1) 
			{
				release(first, last);
				free(last);
			}
			return 0;
		}
	}
}