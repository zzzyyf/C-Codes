#include <stdio.h>
int main()
{
    int n,i,j,k=0;//k���ڼ������ַ���������Ϊt������
    while (scanf("%d",&n),n!=0)
    {
        k=0;
        getchar();
        char s[n][1000];
        for (i=0;i<n;i++)
        {
            scanf("%[^\n]", s[i]);//��������
            getchar();//�ӵ���������'\n'
        }
        char t[1000];
        for (i=0;i<n;i++)//�ϲ�ÿ���ַ���ʱ
        {
            for(j=0;s[i][j]!='\0';j++)//����ÿ���ַ�
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
