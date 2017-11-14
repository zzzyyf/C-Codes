//要求：计算PI的近似值，公式：PI/4 = 1 - 1/3 + 1/5 - ...直到最后一项的绝对值小于1e-5时停止。输出结果占一行，保留9位小数。
//疑惑：为何1. / (n + 2) < 1e-5判断失误？（执行到n=99999就停止了）
#include <stdio.h>
#include <stdlib.h>
int main()
{
	double PI = 1, n = 1,e;
	int i = 1;
	for(;n <= 1e5; n += 2, i++)
	{
		if (i % 2) e = -1.;
		else e = 1.;
		PI += 1. / (n + 2) * e;
	}
	printf("%.9f\n", PI * 4.);
	system("pause");
	return 0;
}