#include <stdio.h>
#define SWAP(x,y,z)(z=x,x=y,y=z)
int main()
{
	int a, b, c, n = 0;
	while (scanf("%d%d", &a, &b) != EOF)
	{
		n++;
		printf("Case %d:\n",n);
		printf("Before Swap:a=%d b=%d\n", a, b);
		SWAP(a, b, c);
		printf("After Swap:a=%d b=%d\n\n", a, b);

	}
	return 0;
}
