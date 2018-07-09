#include <stdio.h>
int main()
{
    int n,i,j,k=0;//k用于计数总字符数，以作为t的索引
    while (scanf("%d",&n),n!=0)
    {
        k=0;
        getchar();
        char s[n][1000];
        for (i=0;i<n;i++)
        {
            scanf("%[^\n]", s[i]);//接收输入
            getchar();//扔掉缓冲区的'\n'
        }
        char t[1000];
        for (i=0;i<n;i++)//合并每个字符串时
        {
            for(j=0;s[i][j]!='\0';j++)//填入每个字符
            {
                t[k]=s[i][j];
                k++;
            }
        }
        t[k]='\0';
        printf("%s\n",t);
    }
    return 0;
}
