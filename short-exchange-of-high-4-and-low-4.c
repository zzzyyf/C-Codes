#include <stdio.h>
int main()
{
	int i;
	unsigned short x, mask, high, low, mask2;
	i = getchar() - '0';
	mask = ~(~0<<4);//11...1->1111 1111 1111 0000->0000 0000 0000 1111
	mask2 = ~(mask + (mask << 12));//1111 0000 0000 1111->0000 1111 1111 0000
	for (; i > 0; i--)
	{
		scanf("%hu", &x);
		high = ((x >> 12) & mask);//�����Ѿ���������high
		low = (x & mask) << 12;//�����Ѿ���������low
		printf("%hu\n", high + low + (x & mask2));//�������λ�����λ������Ľ��
	}
	return 0;
}