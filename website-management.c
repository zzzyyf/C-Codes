#include <stdio.h>
#include <string.h>
typedef struct
{
    char abbr[21];
    char full[41];
    char site[101];
} web;
void main()
{
    int n,i,j;
    n=getchar()-'0';
    web weblist[n],temp;
    for (i=0;i<n;i++)
    {
        scanf("%s%s%s",weblist[i].abbr,weblist[i].full,weblist[i].site);
        getchar();
    }
    for (i=0;i<n;i++) printf("%-20s%-40s%-s\n",weblist[i].abbr,weblist[i].full,weblist[i].site);
    printf("\n");
    for (j=0;j<n-1;j++)
    {
        for (i=0;i<n-1-j;i++)
            if (strcmp(weblist[i].abbr,weblist[i+1].abbr)>0)
                temp=weblist[i],weblist[i]=weblist[i+1],weblist[i+1]=temp;
    }
    for (i=0;i<n;i++)
    {
        printf("%-20s%-40s%s\n",weblist[i].abbr,weblist[i].full,weblist[i].site);
    }
}