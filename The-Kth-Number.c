/*���棬���ַ�������档������ͨ������
#include <stdio.h>
#include <string.h>
int main()
{
	char x[11];
	int k;
	while (scanf("%s %d", x, &k) != EOF)
	{
		if (k <= strlen(x) && k >= 1)printf("%c\n\n", x[strlen(x) - k]);
		else printf("-1\n\n");
	}
	return 0;
}
*/
#include <stdio.h>
int find(unsigned long n, int k)
{
	unsigned long t = 1;
	int t2, x2;
	if (k > 10) return -1;
	for (; k > 1; k--)t *= 10;
	int x = n / t;
	x2 = x;
	if (x == 0) return -1;//���k����n��λ������͵���0
	else if (x >= 10)//kС��n��λ��
	{//˼·�ǰѵ���ѭ��-1��ֱ����λΪ0������ԭ����������ɵó���λ��
		while (--x2 % 10 != 0);
		return x - x2;
	}
	else return x;
}

int main()
{
	unsigned long n;
	int k;
	while (scanf("%lu%d", &n, &k) != EOF)
	{
		printf("%d\n", find(n, k));
	}
	return 0;
}