//输入：int t(t=0时按if执行，t=1时按switch执行，t=2时按两种执行) float a float b 运算符（+-*/），遇EOF结束。
//输出：After if-else/switch processing,the result is : xxx

#include <stdio.h>
int main()
{
	int t;
	float a, b, result;
	char symbol;
	while (scanf("%d",&t) != EOF)
	{
		scanf("%f %f %c", &a, &b, &symbol);
		if (t == 0 || t == 2)
		{
			if (symbol == '+') result = a + b;
			else if (symbol == '-')result = a - b;
			else if (symbol == '*')result = a * b;
			else if (symbol == '/')result = a / b;
			printf("After if-else processing,the result is : %.2f\n", result);
		}
		if (t == 1 || t == 2)
		{
			switch (symbol)
			{
			case '+':
				result = a + b;
				break;
			case '-':
				result = a - b;
				break;
			case '*':
				result = a * b;
				break;
			case '/':
				result = a / b;
				break;
			default:
				break;
			}
			printf("After switch processing,the result is : %.2f\n", result);
			
		}
		printf("\n");
	}
	return 0;
}