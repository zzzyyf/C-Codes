#include <stdio.h>
//查看limits.h得知本机short长度为16bits
//输入将要处理的数据组数n，输入short，以字符形式输出该short的高字节和低字节，中间用,隔开
int main()
{
	int i;//步数
	short x;//输入
	unsigned short mask;
	char high, low;//高、低字节对应值
	i = getchar() - '0';
	for (; i > 0; i--)
	{
		scanf("%hd", &x);
		mask = ~(short)((~0u)<<8);//1111 1111 1111 1111->1111 1111 0000 0000->0000 0000 1111 1111
		low = x & mask;
		high = (x >> 8) & mask;//先把高字节下移再取出
		printf("%c,%c\n", high, low);
	}
	return 0;
}
//问题
//为何把scanf的转换说明设为"%d"时，即用int存放short型时，执行到return 0会报错？