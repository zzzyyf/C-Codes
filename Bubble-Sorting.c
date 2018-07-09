#include <stdio.h>
//取最小-放首位
int main()
{
    int x[10];
    int min,i,j,k;
    int temp;//min,j和k均为索引
    while(scanf("%d",&x[0])!=EOF)
    {
        for (i=1;i<10;i++) scanf("%d",&x[i]);//i为一次性计数器
        min = 0;
        for (j=0;j<10;j++)//经过n-1次排序可以排好
        {
            //单次排序中
            for (k=j;k<10;k++) if (x[k]<x[min]) min=k;//取最小
            temp = x[min],x[min]=x[j],x[j]=temp;//放首位
            min=j+1;//最小位暂时变成后面一位
        }
        for (i=0;i<9;i++) printf("%d->",x[i]);
        printf("%d\n",x[i]);
    }
}
