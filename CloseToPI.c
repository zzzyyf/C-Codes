//Ҫ�󣺼���PI�Ľ���ֵ����ʽ��PI/4 = 1 - 1/3 + 1/5 - ...ֱ�����һ��ľ���ֵС��1e-5ʱֹͣ��������ռһ�У�����9λС����
//�ɻ�Ϊ��1. / (n + 2) < 1e-5�ж�ʧ�󣿣�ִ�е�n=99999��ֹͣ�ˣ�
#include <stdio.h>
#include <stdlib.h>
int main()
{
	double PI = 1, n = 1,e;
	int i = 1;
	for(;n <= 1e5; n += 2, i++)
	{
		if (i % 2) e = -1.;
		else e = 1.;
		PI += 1. / (n + 2) * e;
	}
	printf("%.9f\n", PI * 4.);
	system("pause");
	return 0;
}