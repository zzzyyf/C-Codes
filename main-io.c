#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"

//����
//1.ɾ��ָ�����ݡ���ƽ���ɼ�������δʵ��

//�����ѵ��
//1.��ƺ���ʱ��Ҫ�Ѻ�������ʲô��������ʲô������ʲô�����
//2.�ᴩ�������̵ı���Ҫ���ġ�
//3.ÿһ�鶼Ҫ���㷨����������ʹ����򵥵Ĳ��֡�
int main()
{
	char opt;//�洢ѡ��
	extern int c;
	c = 0;//����ڵ����,0��ʾδ����
	char fileinname[20], fileoutname[20];
	stu *x,*x2;//ɾ������ʱ��
	stu *prev, *next;//ɾ������ʱ��
	printf("��ӭ����ѧ������ϵͳ��");
	while(1)//ʵ���ظ�����
	{
		fflush(stdin);
		printf("\n");
		printf("������ѡ���Ӧ������ѡ��Ҫ���еĲ�����\n1.��������\n2.��ӡ����\n3.ɾ������\n");
		printf("4.��������\n5.ɾ������\n6.����ƽ���ɼ�\n7.��ƽ���ɼ����򣨽���\n8.��������\n9.�˳�\n");
		printf("\n");
		scanf("\n%c", &opt);
		printf("\n");
		switch (opt)
		{
		case '1'://ѡ�񴴽�����
			puts("��ѡ��������Դ��1.�ֶ����룻2.�����ļ���3.�ص��ϼ���������ѡ���Ӧ��������ѡ��");
			scanf("\n%c", &opt);
			printf("\n");
			stu *first = malloc(sizeof(stu));//��������ʱ�ã�������ĵ�һ��Ԫ��
			first->no = 0;//��ų�ʼΪ0��������Զ����
			stu *last;//��������һ��Ԫ��

			//���������ѡ��
			switch (opt)
			{
			case '1'://ѡ���ֶ�����
				printf("\n");
				last = create(first);//�����ֶ���������ĺ��������Ѵ��������һ���ڵ�ĵ�ַ������ַlast
				last->next_stu = first, first->prev_stu = last;//��β˫������
				c ++;//�Ѿ�������һ������
				break;
			case '2'://ѡ�������ļ�
				printf("\n");
				printf("������洢���ݵ��ļ��������������λ��ͬһĿ¼����");
				scanf("%s", fileinname);//��ȡ������ݵ��ļ���
				printf("\n");
				FILE *filein;
				if ((filein = fopen(fileinname, "r"))== 0) 
				{
					puts("��ȡ�ļ�ʧ�ܣ������ļ���");//������ȡ�ļ���������
					break;
				}
				last = read(filein, first);//���ô�������ĺ������������һ���ڵ�
				if (last != NULL) last->next_stu = first, first->prev_stu = last;//��β˫������
				break;
			}
			break;
		case '2'://ѡ���ӡ����
			if (c != 0) printList(stdout, 1, first, first);
			else printf("���ȴ�������\n");
			break;
		case '3'://ѡ��ɾ������
			//�������������
			if (c != 0)
			{
				release(first, last);
				if (c != 1) free(last);//���ֻ������һ��Ԫ��Ҫ������һ��
				c = 0;
			}
			else printf("���ȴ�������\n");
			break;
		case '4'://ѡ���������
			if (c == 0)
			{
				printf("���ȴ�������\n");
				break;
			}
			last->next_stu = malloc(sizeof(stu));//������һ���µĽڵ�
			last->next_stu->prev_stu = last;//ĩ������ǰ������
			last = create(last->next_stu);
			last->next_stu = first, first->prev_stu = last;//��β˫������
			last->no = last->prev_stu->no + 1;
			break;
		case '5'://ѡ��ɾ������
			if (c == 0)
			{
				printf("���ȴ�������\n");
				break;
			}
			x = first;
			puts("��Ҫ���������Զ�λ��ɾ��������(y/n)");
			scanf("\n%c", &opt);
			printf("\n");
			if (opt == 'y') search(first);
			puts("������Ҫɾ���ڵ����ţ�");
			scanf("\n%c", &opt);
			printf("\n");
		//ɾ��ָ����ŵ�����
			if (opt == '1')//ɾ����һ��
			{
				if (first == next)//����ֻ��һ���ڵ�
				{
					release(first, last);
					printf("������Ϊ�գ������´�������\n");
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
					printf("ɾ���ɹ���\n");
				}
			}
			else if (opt - '0' == last->no)//ɾ�����һ��
			{
				prev = last->prev_stu;
				free(last);
				last = prev;
				last->next_stu = first; first->prev_stu = last;
				c--;
				printf("ɾ���ɹ���\n");
			}
			else do
			{
				if (x->no  == opt - '0') 
				{
					prev = x->prev_stu, next = x->next_stu;
					x2 = x->next_stu;//��ǰ��x���¸��ڵ����������ֹx���ͷź��Ҳ���x���¸���ַ
					free(x);
					x = x2;//����
					c--;
					printf("ɾ���ɹ���\n");
					prev->next_stu = next, next->prev_stu = prev;
				}
				else x = x->next_stu;//������һ���ڵ�
			} while (x != first);//û�д�ͷ����һ��ʱ
			if (c != 0)//���¸����
			{
				x = x->prev_stu;
				do
				{
					x->no = c--;
					x = x->prev_stu;//������һ���ڵ�
				} while (x != last);//û�д�ͷһ��ʱ
				c = x->no;//����ȡ������ڵ����
			}
			else printf("������Ϊ�գ������´�������\n");
			break;
		case '6'://ѡ�����ƽ���ɼ�
			if (c == 0)printf("��δ�����������ȴ�������\n");
			else average(first, first);
			break;
		case '7'://ѡ��ƽ���ɼ����򣨽���
			if (c <= 1)printf("������������������������\n");
			else
			{
				stu *max = malloc(sizeof(stu));//����������
				*max = *first;//�������һ����Ϊ�������һ��
				max->prev_stu = max, max->next_stu = max;//������˫��ջ�
				if (max->grade_avg <= 0.09f)
				{
					printf("���ȼ���ƽ���ɼ���\n");
					break;
				}
				else max = sorting(first, max, first->next_stu);
				printf("������ɣ�������£�\n");
				printList(stdout, 1, max, max);
				puts("���������ᱣ���ڳ����С���Ҫ������������Ϊ�ļ���(y/n)");
				scanf("\n%c", &opt);
				printf("\n");
				if (opt == 'y')
				{
					printf("��ΪҪ����������ļ��������ļ�������򴢴���ͬһĿ¼����");
					scanf("%s", fileoutname);
					printf("\n");
					FILE *fileout = fopen(fileoutname, "w");
					printf("��ѡ�񱣴�ѡ�1.��ʱ���棨�޸�ʽ���ɶ�ȡ����2.���հ棨����ʽ�����ɶ�ȡ��");
					scanf("\n%c", &opt);
					printf("\n");
					switch (opt)
					{
					case '1'://ѡ���޸�ʽ����
						printList(fileout, 0, max, max);
						printf("����ɹ���\n");
						break;
					case '2'://ѡ�����ʽ����
						printList(fileout, 1, max, max);
						printf("����ɹ���\n");
						break;
					}
				}
				release(max, max->prev_stu);
			}
			break;
		case '8'://ѡ�񱣴�����
			if (c == 0)
			{
				printf("���ȴ�������\n");
				break;
			}
			printf("��ΪҪ����������ļ��������ļ�������򴢴���ͬһĿ¼����");
			scanf("%s", fileoutname);
			printf("\n");
			FILE *fileout = fopen(fileoutname, "w");
			printf("��ѡ�񱣴�ѡ�1.��ʱ���棨�޸�ʽ���ɶ�ȡ����2.���հ棨����ʽ�����ɶ�ȡ��");
			scanf("\n%c", &opt);
			switch (opt)
			{
			case '1'://ѡ���޸�ʽ����
				printList(fileout, 0, first, first);
				printf("����ɹ���\n");
				break;
			case '2'://ѡ�����ʽ����
				printList(fileout, 1, first, first);
				printf("����ɹ���\n");
				break;
			}
			break;
		case '9'://ѡ���˳�
			//�������������
			if (c != 0) 
			{
				release(first, last);
				free(last);
			}
			return 0;
		}
	}
}