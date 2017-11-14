#include <stdio.h>
int main()
{

	int year, month, day;
	int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int daynum;
	while (scanf("%d", &year) != EOF)
	{
		scanf("%d %d", &month, &day);
		daynum = 0;
		if (!(year % 400) || (year % 100) && !(year % 4)) days[1] = 29;
		else days[1] = 28;
		for (; month > 1; month--)daynum += days[month - 2];
		daynum += day;
		printf("该日期是这一年中的第%d天\n", daynum);
	}
	return 0;
}

/*第二种
	int year, month, day;
	while (scanf("%d %d %d", &year, &month, &day) != EOF)
	{
		int n = 0;
		switch (month)
		{
		case 12:
			n += 30;
		case 11:
			n += 31;
		case 10:
			n += 30;
		case 9:
			n += 31;
		case 8:
			n += 31;
		case 7:
			n += 30;
		case 6:
			n += 31;
		case 5:
			n += 30;
		case 4:
			n += 31;
		case 3:
			if (!(year % 400) || year % 400 && !(year % 4)) n += 29;
			else n += 28;
		case 2:
			n += 31;
		}
		n += day;
		printf("该日期是这一年中的第%d天\n", n);
	}
	return 0;
}
*/
//以上功能一致但不获通过