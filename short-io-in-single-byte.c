#include <stdio.h>
//�鿴limits.h��֪����short����Ϊ16bits
//���뽫Ҫ�������������n������short�����ַ���ʽ�����short�ĸ��ֽں͵��ֽڣ��м���,����
int main()
{
	int i;//����
	short x;//����
	unsigned short mask;
	char high, low;//�ߡ����ֽڶ�Ӧֵ
	i = getchar() - '0';
	for (; i > 0; i--)
	{
		scanf("%hd", &x);
		mask = ~(short)((~0u)<<8);//1111 1111 1111 1111->1111 1111 0000 0000->0000 0000 1111 1111
		low = x & mask;
		high = (x >> 8) & mask;//�ȰѸ��ֽ�������ȡ��
		printf("%c,%c\n", high, low);
	}
	return 0;
}
//����
//Ϊ�ΰ�scanf��ת��˵����Ϊ"%d"ʱ������int���short��ʱ��ִ�е�return 0�ᱨ��