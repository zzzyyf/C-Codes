#include <stdio.h>
int main()
{
	int a, b, c;
	while (scanf("%d%d%d",&a, &b, &c) != EOF)
	{
		if ((a >= b && a <= c) || (a >= c && a <= b)) printf("A:%d", a);
		else if ((b >= a && b <= c) || (b >= c && b <= a)) printf("B:%d", b);
		else printf("C:%d", c);
	}
	return 0;
}