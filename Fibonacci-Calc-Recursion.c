#include <stdio.h>
int Calc(int a, int b, int c, int n)
{
	if (n-- - 2 > 0)
	{
		c = a + b;
		a = b, b = c;
		c = Calc(a, b, c, n);
	}
	return c;
}
//쳲������ݹ���û�и��õ�д����
int main()
{
	int x;
	while (scanf("%d", &x) != EOF)
	{
		if (x < 3)
		{
			printf("%d\n", 1);
		}
		else printf("%d\n", Calc(1, 1, 0,x));
	}
	return 0;
}
