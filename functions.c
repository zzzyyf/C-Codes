#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "myheader.h"

int opt1;
extern int c;
/*�������Ԫ��*/
void printstu(FILE *stream, stu* a)
{
	if (stream == stdout) printf("\n");
	fprintf(stream, "��ţ�%d\n������%s\nѧ�ţ�%s\n�Ա�%c\n", a->no, a->name, a->id_num, a->gender);
	fprintf(stream, "���ĳɼ���%d\n��ѧ�ɼ���%d\nӢ��ɼ���%d\nƽ���ɼ���%.1f\n", a->grade_chi, a->grade_mat, a->grade_eng, a->grade_avg);
	if (stream == stdout) printf("\n");
}

/* �ֶ� ���������������ĩ�����Ԫ�أ�ʹ��ǰ���ȴ���һ��Ԫ��*/
stu* create(stu* new)//��������ĺ������ɴ��ļ��ж�ȡ��Ҳ���ֶ�����
{
	puts("������ѧ��������"), scanf("%s", new->name);
	puts("������ѧ��ѧ�ţ�"), scanf("%s", new->id_num);		
	puts("������ѧ���Ա�m��ʾ�У�w��ʾŮ��"), scanf("\n%[mw]", &new->gender);
	puts("��ֱ�����ѧ��������ɼ����м��ÿո������"), scanf("%d %d %d", &new->grade_chi, &new->grade_mat, &new->grade_eng);
	if (c == 0) new->prev_stu = NULL;
	new->next_stu = NULL;
	new->grade_avg = .0;

	c ++;//�ɹ�����һ��Ԫ��
	new->no = c;

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
			(r3 = fscanf(in, "\n%[mw]", &new->gender) != 1) ||
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
	c++;
	new->no = c;
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

/*��������ĵ�һ���ڵ㣬��������Ĺؼ��ֲ��ҽڵ㣬����ҵ������нڵ�*/
void search(stu *first)
{
	searchkey *k = malloc(sizeof(searchkey));
	puts("������ѡ��ѡ�������ؼ������ڵ��ֶΣ�1.��ţ�2.������3.ѧ�ţ�4.�Ա�5.���ĳɼ���6.��ѧ�ɼ���7.Ӣ��ɼ���8.ƽ���ɼ�");
	scanf("%d", &k->t);
	k->t--;
	stu *current = first;
	switch (k->t)
	{
	case NO://����Ų���
		puts("������Ҫ���ҵ���ţ�");
		scanf("%d", &k->k.gender);
		do
		{
			if (current->no == k->k.gender) printstu(stdout, current);//���������ŵ��ڽڵ����ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		} while (current != first);//û�д�ͷ����һ��ʱ
		break;
	case NAME://����������
		puts("������Ҫ���ҵ�������");
		scanf("%s", k->k.strings);
		do
		{
			if (strstr(current->name,k->k.strings)) printstu(stdout, current);//�������������ڵ������ֶ���ͬʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		} while (current != first);//û�д�ͷ����һ��ʱ
		break;
	case ID://��ѧ�Ų���
		puts("������Ҫ���ҵ�ѧ�ţ�");
		scanf("%s", k->k.strings);
		do
		{
			if (strstr(current->id_num, k->k.strings)) printstu(stdout, current);//�������ѧ����ڵ�ѧ���ֶ���ͬʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		} while (current != first);//û�д�ͷ����һ��ʱ
		break;
	case GENDER://���Ա����
		puts("������Ҫ���ҵ��Ա�");
		scanf("%c", &k->k.gender);
		do
		{
			if (current->gender == k->k.gender) printstu(stdout, current);//��������Ա���ڽڵ��Ա�ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		} while (current != first);//û�д�ͷ����һ��ʱ
		break;
	case CHI://�����ĳɼ�����
		puts("������Ҫ���ҵĳɼ��������辫ȷƥ�䣩��");
		scanf("%d", &k->k.grades);
		do
		{
			if (current->grade_chi == k->k.grades) printstu(stdout, current);//����������ĳɼ����ڽڵ�����ĳɼ�ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		} while (current != first);//û�д�ͷ����һ��ʱ
		break;
	case MAT://����ѧ�ɼ�����
		puts("������Ҫ���ҵĳɼ��������辫ȷƥ�䣩��");
		scanf("%d", &k->k.grades);
		do
		{
			if (current->grade_mat == k->k.grades) printstu(stdout, current);//���������ѧ�ɼ����ڽڵ���ѧ�ɼ�ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		} while (current != first);//û�д�ͷ����һ��ʱ
		break;
	case ENG://��Ӣ��ɼ�����
		puts("������Ҫ���ҵĳɼ��������辫ȷƥ�䣩��");
		scanf("%d", &k->k.grades);
		do
		{
			if (current->grade_eng == k->k.grades) printstu(stdout, current);//�������Ӣ��ɼ����ڽڵ�Ӣ��ɼ�ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		} while (current != first);//û�д�ͷ����һ��ʱ
		break;
	case AVG://��ƽ���ɼ�����
		puts("������Ҫ���ҵĳɼ��������辫ȷƥ�䣩��");
		scanf("%f", &k->k.average);
		do
		{
			if (fabs(current->grade_avg - k->k.average) <= 0.09f) printstu(stdout, current);//�������ƽ���ɼ����ڽڵ�ƽ���ɼ�ʱ����ýڵ�
			current = current->next_stu;//������һ���ڵ�
		} while (current != first);//û�д�ͷ����һ��ʱ
		break;
	}

}

/*���վ�����ĵ�һ���ڵ㣬������ĵ�һ���ڵ�;�������Ƚϵ���Ѿ�������Ƚϵ��ƽ���ɼ������������������������ĵ�һ���ڵ�*/
stu *sorting(stu *first,stu *max, stu *old)//oldΪ��������Ƚϵ���
{
	stu *next = malloc(sizeof(stu));
	*next = *old;
	stu *new = max->prev_stu;//newΪ��������ĩһ���ƽ���ɼ���Сһ�
	do
	{
		if ((next->grade_avg - new->grade_avg) <= 0.09f)//���nextС�ڵ�����С��
		{
			next->next_stu = new->next_stu;
			new->next_stu->prev_stu = next;
			new->next_stu = next;
			next->prev_stu = new;
			//��next���������Ҫ��ͨ��next֮ǰ�İ�next֮��ĺ�next˫�����ӣ��ٰ�next��next֮ǰ��˫�����ӡ�
		}
		else new = new->prev_stu;//next������С�����С��ǰһ��Դ���Ƚ�
	} while (new != max);//������Ľڵ�û�б�ȫ���ȶ�һ��
	if ((next->grade_avg - max->grade_avg) > 0.09f)//next��max����
	{
		max->prev_stu->next_stu = next;
		next->prev_stu = max->prev_stu;
		next->next_stu = max;
		max->prev_stu = next;
		max = next;
		//��next����max��last֮�䣬��max��Ϊnext
	}
	else //nextС�ڵ���max������max��������
	{
		max->next_stu->prev_stu = next;
		next->next_stu = max->next_stu;
		next->prev_stu = max;
		max->next_stu = next;
	}
	if (old->next_stu != first)//������û���������
	{
		old = old->next_stu;//�����Ѿ����������һ�������������ĩһ��Ƚ�
		sorting(first, max, old);
	}
	else return max;
}