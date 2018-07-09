#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    char c;
    struct node *next;
} nod;
int main()
{
    nod *p = malloc(sizeof(nod)),*h=p,*t=p;
    p->next = NULL;
    char temp;
    int i;
    for (i=0;(temp=getchar())!='#';i++)
    {
        t->c=temp;
        t->next = malloc(sizeof(nod));
        t->next->next = NULL;
        t=t->next;
    }

    char str[i];
    for (i=0,t=h;t->next!=NULL;i++,t=t->next) str[i]=t->c;
    str[i]='\0';
    for (i=0,t=h;t->next!=NULL;i++,t=t->next) printf("%c",t->c);
    printf("\n\n");
    printf("%s\n",str);
    return 0;
}
