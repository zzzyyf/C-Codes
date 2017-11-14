#include <stdio.h>
int main()
{
	int a, b, c, n, n2;
	while (1)
	{
		n2 = 0;
		scanf("%d", &n);
		if (n == 0)break;
		if (n >= 3)
		{
			a = 0, b = 1;
			printf("%10d", 1);
			while (n > 1)
			{
				c = a + b;
				printf("%10d", c);
				a = b, b = c;
				n2++, n--;
				if (!((n2 + 1) % 8)) printf("\n");
			}
			printf("\n");
			if (((n2 + 1) % 8)) printf("\n");
		}
		else printf("Error!\n");
	}
	return 0;
}