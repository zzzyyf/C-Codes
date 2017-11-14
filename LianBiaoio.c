//�ӱ�׼�����ȡһ�е�����Ȼ����������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct island
{
	char *name;
	const char *opens;
	const char *closes;
	struct island *next;
}island;

island* create(char *name)
{
	island *i = malloc(sizeof(island));
	i->name = strdup(name);//������ĵ�����ջ�ϵ�name[80]���鸴�Ƶ������Է�������
	i->opens = "09:00";
	i->closes = "17:00";
	i->next = NULL;
	return i;
}
void display(island *x)
{
	printf("Name: %s\nOpens:%s - %s\n", x->name, x->opens, x->closes);
}
int main()
{
	island *start = NULL;
	island *n = NULL;
	island *next = NULL;
	char name[80];
	for (; fgets(name, 80, stdin) != NULL; n = next)
	{//����ĵ�����Ϊ��ʱѭ����ѭ����Ϻ��n�ĵ�ַ��Ϊ��ַnext
		next = create(name);//�ѵ�ַnext��Ϊ�Ե�ǰ���������Ľṹi�ĵ�ַ
		if (start == NULL)//�������ͷ�ĵ�ַΪ��
			start = next;//�����뵱ǰ�ṹ�ĵ�ַ
		if (n != NULL)//���n�ĵ�ַ��Ϊ�գ���start��next�ֶ���ô�졣����
			n->next = next;//�Ͱ�n��next�ֶ���Ϊ��ǰ���������Ľṹ�ĵ�ַ
	}
	display(start);
	system("pause");
}
