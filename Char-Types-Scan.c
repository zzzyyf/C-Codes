#include <stdio.h>
#include <string.h>
int main()
{
    int flag[12],i,iofnum;
    for (iofnum = 0;iofnum <= 11;iofnum++)
            flag[iofnum] = 0;
    char passage[1000];
    scanf("%[^#]",passage);
    for (i = 0;i < strlen(passage);i++)
    {
        //¸÷Êı×Ö×Ö·û
        for (iofnum = 0;iofnum < 10;iofnum++)
            if (passage[i] == iofnum+'0')flag[iofnum]++;
        //¸÷×ÖÄ¸
        if((passage[i]>='A'&&passage[i]<='Z') || (passage[i]>='a'&&passage[i]<='z'))
            flag[10]++;
        else if(passage[i]>='0' && passage[i]<='9');
        else flag[11]++;
    }
    for (iofnum = 0;iofnum < 10;iofnum++)
        printf("Number %d: %d\n",iofnum,flag[iofnum]);
    printf("characters: %d\n",flag[10]);
    printf("other: %d\n",flag[11]);
}
