//��ѵ��
//1.����double����double�����ȸ�
//2.ÿ��ѭ����Ҫ����Ƿ�����Ҫ��ʼ���ı���
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n, t, sum = 0, i, p = 0;//nΪ����������tΪ�Ƿ�ʹ��continue��sumΪ�����ܺͣ�iΪһ�����ݵ���ţ�pΪ��������
	int x[10];
	double average;
	scanf("%d", &n);
	for (;n > 0;n--)
	{
		scanf("%d %d %d %d %d %d %d %d %d %d %d", &t, &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9]);
		switch (t)
		{
		case 0://����continue��ʽ����
			i = 0,sum = 0,p = 0;
			for (; i < 10; i++)
			{
				if (x[i] < 0) continue;
				p++;
				sum += x[i];
			}
			if (p != 0)
			{
				average = sum / (float)p;
				printf("In \"continue\" way,numbers=%d,average=%.6f\n", p, average);
				break;
			}
			else break;
		case 1://����continue��ʽ
			i = 0, sum = 0, p = 0;
			for (; i < 10; i++)
			{
				if (x[i] >= 0)
				{
					p++;//��������+1
					sum += x[i];//�����ܺ�
				}
				if (i == 9 && p != 0)
				{
					average = sum / (float)p;
					printf("In \"no continue\" way,numbers=%d,average=%.6f\n", p, average);
					break;
				}
				else if (i == 9 && p == 0) break;
			}
			break;
		}
	}
	system("pause");
	return 0;
}
