#include <stdio.h>
void mycpy(char str[], char *target, int n);
int main()
{
    char str[1000],target[1000];
    char *p = target;
    int n,n2,i;
    scanf("%d",&n2);
    getchar();
    while(n2--)
    {
        scanf("%[^\n]",str);
        getchar();
        scanf("%d",&n);
        getchar();
        mycpy(str,p,n);
        printf("%s\n",target);
        //没必要初始化target，因为有'\0'在就知道字符串结束了，而'\0'之前的都已经被改过了
    }
	return 0;
}
void mycpy(char str[], char *target, int n)
{
    int i;
    for(i = 0;i < n;i++)*(target + i) = str[i];
    *(target + i) = '\0';
}
