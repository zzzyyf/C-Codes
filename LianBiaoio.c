//从标准输入读取一列岛名，然后连成链表。
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
	i->name = strdup(name);//把输入的岛名从栈上的name[80]数组复制到堆上以防被更改
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
	{//输入的岛名不为空时循环；循环完毕后把n的地址设为地址next
		next = create(name);//把地址next设为以当前岛名创建的结构i的地址
		if (start == NULL)//如果链表开头的地址为空
			start = next;//则填入当前结构的地址
		if (n != NULL)//如果n的地址不为空（那start的next字段怎么办。。）
			n->next = next;//就把n的next字段设为当前岛名创建的结构的地址
	}
	display(start);
	system("pause");
}
