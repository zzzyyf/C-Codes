#include <stdio.h>
int main()
{
	int a, b;
	int divisor, multiple;
	int n;
	while (1)
	{
		divisor = multiple = 0;
		scanf("%d%d", &a, &b);
		if (a == 0 && b == 0)break;
		n = 1;
		while (n <= b)
		{
			if (a % n == 0 && b % n == 0)
				divisor = n;
			n++;
		}
		n = a * b;
		while (n > 0)
		{
			if (n % b == 0 && n % a == 0)
				multiple = n;
			n--;
		}
		printf("%d %d\n", divisor, multiple);
	}
	return 0;
}