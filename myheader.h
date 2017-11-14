#pragma warning(disable:4996)
#include <stdio.h>
typedef struct stu
{
	struct stu *prev_stu;//��һ��ѧ��
	struct stu *next_stu;//��һ��ѧ��
	int no;//���
	char name[20];//����
	char id_num[20];//ѧ��
	char gender;//�Ա�m=�У�w=Ů
	int grade_chi;//���ĳɼ�
	int grade_mat;//��ѧ�ɼ�
	int grade_eng;//Ӣ��ɼ�
	float grade_avg;//ƽ���ɼ�
}stu;

union keyword//�洢����ʱʹ�õĹؼ���
{
	char strings[20];//������ѧ��
	char gender;//�Ա�����
	int grades;//������ɼ�
	float average;//ƽ���ɼ�
};

enum type { NO, NAME, ID, GENDER, CHI, MAT, ENG, AVG };//�ؼ��ֵ�����

typedef struct//�ؼ��ֵ����ݺ�����
{
	union keyword k;//����Ĺؼ���
	enum type t;//�ؼ�������
}searchkey;

int c;//�Ƿ񴴽�����

/*�������Ԫ��*/
void printstu(FILE *stream, stu* a);

/*���������������ĩ�����Ԫ�أ�ʹ��ǰ���ȴ���һ��Ԫ��*/
stu* create(stu* new);//�ֶ���������ĺ���

/*���ļ��ж�ȡ���������ش����ɹ������һ���ڵ�ʹ��ǰ���ȴ�����һ��Ԫ��*/
stu* read(FILE *in, stu *new);

/*�ͷ�֮ǰ��������жѴ洢�ռ�*/
void release(stu* a, stu* z);

/*�����������*/
void printList(FILE *stream,int printopt, stu* first1, stu* first2);//printoptΪ0ʱ��ʾ�޸�ʽ�����Ϊ1ʱ��ʾ����ʽ���

/*�޸�ʽ������ļ��Ա��´ζ�ȡʹ��*/
void printforR(FILE *stream, stu* a);

/*����ÿ��ѧ����ƽ���ɼ�*/
void average(stu *a, stu* first);

/*��������Ĺؼ��ֲ��ҽڵ�*/
void search(stu *first);

/*������Ľڵ㰴��ƽ���ɼ���������*/
stu *sorting(stu *first, stu *max, stu *old);