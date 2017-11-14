//教训：
//1.能用double就用double，精度高
//2.每个循环都要检查是否有需要初始化的变量
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n, t, sum = 0, i, p = 0;//n为数据组数，t为是否使用continue，sum为正数总和，i为一组数据的序号，p为正数个数
	int x[10];
	double average;
	scanf("%d", &n);
	for (;n > 0;n--)
	{
		scanf("%d %d %d %d %d %d %d %d %d %d %d", &t, &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9]);
		switch (t)
		{
		case 0://需用continue方式处理
			i = 0,sum = 0,p = 0;
			for (; i < 10; i++)
			{
				if (x[i] < 0) continue;
				p++;
				sum += x[i];
			}
			if (p != 0)
			{
				average = sum / (float)p;
				printf("In \"continue\" way,numbers=%d,average=%.6f\n", p, average);
				break;
			}
			else break;
		case 1://不用continue方式
			i = 0, sum = 0, p = 0;
			for (; i < 10; i++)
			{
				if (x[i] >= 0)
				{
					p++;//正数个数+1
					sum += x[i];//计入总和
				}
				if (i == 9 && p != 0)
				{
					average = sum / (float)p;
					printf("In \"no continue\" way,numbers=%d,average=%.6f\n", p, average);
					break;
				}
				else if (i == 9 && p == 0) break;
			}
			break;
		}
	}
	system("pause");
	return 0;
}
