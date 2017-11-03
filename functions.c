#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myheader.h"

int opt1;
extern int c;
/*�������Ԫ��*/
void printstu(FILE *stream, stu* a)
{
	if (stream == stdout) printf("\n");
	fprintf(stream, "��ţ�%c\n������%s\nѧ�ţ�%s\n�Ա�%c\n", a->no, a->name, a->id_num, a->gender);
	fprintf(stream, "���ĳɼ���%d\n��ѧ�ɼ���%d\nӢ��ɼ���%d\nƽ���ɼ���%.1f\n", a->grade_chi, a->grade_mat, a->grade_eng, a->grade_avg);
	if (stream == stdout) printf("\n");
}

/* �ֶ� ���������������ĩ�����Ԫ�أ�ʹ��ǰ���ȴ���һ��Ԫ��*/
stu* create(stu* new)//��������ĺ������ɴ��ļ��ж�ȡ��Ҳ���ֶ�����
{
	puts("������ѧ��������"), scanf("%s", new->name);
	puts("������ѧ��ѧ�ţ�"), scanf("%s", new->id_num);		
	puts("������ѧ���Ա�m��ʾ�У�w��ʾŮ��"), scanf("\n%c", &new->gender);
	puts("��ֱ�����ѧ��������ɼ����м��ÿո������"), scanf("%d %d %d", &new->grade_chi, &new->grade_mat, &new->grade_eng);
	new->no++;
	new->prev_stu = NULL;
	new->next_stu = NULL;
	new->grade_avg = .0;

	c = 1;//�ɹ�����
	printf("�����ڵ�ɹ����������Ӧ����ѡ����һ��������1.����������2.Ԥ����ǰѧ�������ݣ�3.��ɴ�����Ĭ�ϣ�");
	scanf("%d", &opt1);
	printf("\n");
	if (opt1 == 1) 
	{
		stu *next = malloc(sizeof(stu));//�����¸��ڵ�
		next->prev_stu = new, new->next_stu = next;//�¸��ڵ������ϸ��ڵ㣬�ϸ��ڵ������¸��ڵ�
		create(next); //��������
	}
	else if (opt1 == 2)
	{
		printstu(stdout, new);
		printf("�������Ӧ����ѡ����һ��������1.����������2.��ɴ�����Ĭ�ϣ�");
		scanf("%d", &opt1);
		printf("\n");
		if (opt1 == 1) 
		{
			stu *next = malloc(sizeof(stu));//�����¸��ڵ�
			next->prev_stu = new, new->next_stu = next;//�¸��ڵ������ϸ��ڵ㣬�ϸ��ڵ������¸��ڵ�
			create(next);//��������
		}
		else return new;
	}
	else return new;
}

/*���ļ��ж�ȡ������,ʹ��ǰ���ȴ�����һ��Ԫ��*/
stu* read(FILE *in, stu *new) 
{
	int r1, r2, r3, r4;
	r1 = r2 = r3 = r4 = 0;
	if (r1 = fscanf(in, "%s[^\n]", new->name) != EOF)//�ļ�û�ж�ȡ���
	{
		if ((r1 != 1) ||
			(r2 = fscanf(in, "%s[^\n]", new->id_num) != 1) ||
			(r3 = fscanf(in, "\n%c", &new->gender) != 1) ||
			(r4 = fscanf(in, "%d %d %d %f", &new->grade_chi, &new->grade_mat, &new->grade_eng, &new->grade_avg) < 3))//�����ֶζ�ȡ����
		{
			puts("���ֶζ�ȡ���������ȡ���ļ���");
			if (c != 0)//�ж�ȡ�ɹ��Ľڵ�
			{
				stu *last = new->prev_stu;//�洢���һ�������ɹ��Ľڵ�
				free(new);//�����ȡ����Ľڵ�
				return last;//�������һ�������ɹ��Ľڵ㣬�˳�����
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
		puts("��ȡ��ɣ�");
		stu *last = new->prev_stu;
		free(new);
		return last;
	}
	if(c == 0) new->prev_stu = NULL;
	new->next_stu = NULL;
	new->grade_avg = .0;
	new->no++;
	c = 1;
	stu *next = malloc(sizeof(stu));//�¸��ڵ�
	next->prev_stu = new, new->next_stu = next;//�¸��ڵ������ϸ��ڵ㣬�ϸ��ڵ������¸��ڵ�

	stu *final = read(in, next);
	return final;
}

/*�ͷ�֮ǰ��������жѴ洢�ռ�*/
void release(stu* a,stu* z)
{
	stu *b = a->next_stu;//�ȴ洢a����һ���ڵ㣬��ֱֹ�����a���Ҳ�����һ��
	free(a);//���a�����нڵ�
	if (b != z) release(b,z);//�����һ���ڵ㲻�ǵ�һ���ڵ㣨û������꣩���Ͷ���һ���ڵ����release��ֱ����һ��Ϊ�գ���Ϊ���һ���ڵ�ָ���һ��������һ���类����ˣ�
}

/*�����������*/
void printList(FILE *stream, int printopt, stu* first1, stu* first2)//printoptΪ0ʱ��ʾ�޸�ʽ�����Ϊ1ʱ��ʾ����ʽ���
{
	stu *current = first1;
	if (printopt == 1) printstu(stream, current);//ѡ��Ϊ1�����ʽ���
	else printforR(stream, current);//ѡ��Ϊ2���޸�ʽ���
	if (current->next_stu != first2)
	{
		current = current->next_stu;//������һ���ڵ�
		printList(stream, printopt, current, first2);
	}
}

/*�޸�ʽ������ļ��Ա��´ζ�ȡʹ��*/
void printforR(FILE *stream, stu* a)
{
	fprintf(stream, "%s\n%s\n%c\n", a->name, a->id_num, a->gender);
	fprintf(stream, "%d %d %d %.1f\n", a->grade_chi, a->grade_mat, a->grade_eng, a->grade_avg);
}

/*����ÿ��ѧ����ƽ���ɼ�*/
void average(stu *a, stu* first)
{
	a->grade_avg = (a->grade_chi + a->grade_mat + a->grade_eng) / 3.0;
	if (a->next_stu != first)
	{
		a = a->next_stu;
		average(a, first);
	}
}

/*��������Ĺؼ��ֲ��ҽڵ�*/
void search(key *k, stu *first)
{
	stu *current = first;
	switch (k->t)
	{
	case NO://����Ų���
		while (current->no != first->no)//û�д�ͷ����һ��ʱ
		{
			if (current->no == k->k.gender) printstu(stdout, current);//���������ŵ��ڽڵ����ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		}
		break;
	case NAME://����Ų���
		while (current->name != first->name)//û�д�ͷ����һ��ʱ
		{
			if (!strcmp(current->name,k->k.strings)) printstu(stdout, current);//�������������ڵ������ֶ���ͬʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		}
		break;
	case ID://����Ų���
		while (current->id_num != first->id_num)//û�д�ͷ����һ��ʱ
		{
			if (!strcmp(current->id_num, k->k.strings)) printstu(stdout, current);//�������ѧ����ڵ�ѧ���ֶ���ͬʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		}
		break;
	case GENDER://����Ų���
		while (current->gender != first->gender)//û�д�ͷ����һ��ʱ
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//��������Ա���ڽڵ��Ա�ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		}
		break;
	case CHI://�����ĳɼ�����
		while (current->gender != first->gender)//û�д�ͷ����һ��ʱ
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//��������Ա���ڽڵ��Ա�ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		}
		break;
	case MAT://����Ų���
		while (current->gender != first->gender)//û�д�ͷ����һ��ʱ
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//��������Ա���ڽڵ��Ա�ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		}
		break;
	case ENG://����Ų���
		while (current->gender != first->gender)//û�д�ͷ����һ��ʱ
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//��������Ա���ڽڵ��Ա�ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		}
		break;
	case AVG://����Ų���
		while (current->gender != first->gender)//û�д�ͷ����һ��ʱ
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//��������Ա���ڽڵ��Ա�ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		}
		break;
	}

}