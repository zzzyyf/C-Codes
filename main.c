/**
 * poj 1753 flip game
 */
#include <stdio.h>

int main()
{
    unsigned int plan = 0x00000000; // 从MSB第23位到LSB第8位，哪一位为1表示翻转该位对应的棋子。运行时从0到ffff枚举，即从上到下，从左到右。
    unsigned int singleMask = 0x00800000; // 操作某一位使用的掩码
    unsigned int board = 0, tempBoard=0; // 读入的盘面状态，中间16位有效，1为white，0为black
    int i, flipTimes=0, minFlip=17; // 最后minFlip==17表示无解
    int solved = 0; // 1表示解出，0表示未解出
    // 如此，第0个棋子每次翻转，第1个棋子每2次翻转……以此类推。
    unsigned int flipOps[16]={0x00c80000, 0x00e40000, 0x00720000, 0x00310000,
                     0x008c8000, 0x004e4000, 0x00272000, 0x00131000,
                     0x0008c800, 0x0004e400, 0x00027200, 0x00013100,
                     0x00008c00, 0x00004e00, 0x00002700, 0x00001300}; // 决定翻转每个棋子后，对应的所有翻转操作。第0个对应第15位的翻转，以此类推。
    char input[16]; // 从上到下，从左到右，以此类推。
    scanf("%4c %4c %4c %4c", input, &input[4], &input[8], &input[12]);
    // 确定盘面状态
    for(i=0;i<16;i++){
        if(input[i]=='w'){
            board+=singleMask>>i;
        }
    }
    // 开始枚举，每次决定对plan中是1的位进行翻转（需要记录是1的位的总数和目前的最小值），然后执行具体的翻转操作，再检验是否等于0x00000000或0x00ffff00.
    for(;plan<0xffff00;plan+=0x100){
        tempBoard = board;
        flipTimes=0;
        solved = 0;
        for(i=0;i<16;i++){
            // 若plan的第15-i+8位为1，表示翻转第i个棋子
            if((plan & singleMask>>i)!=0){
                flipTimes++;
                // 翻转第i个棋子即对temp临时盘面用flipOps[i]进行逐位取反（按位异或）
                tempBoard = tempBoard ^ flipOps[i];
            }
            if(i==11 && ((tempBoard & 0x00ff0000) != 0 && (tempBoard & 0x00ff0000) != 0x00ff0000)){
                // 上3行已经被解出，此时上2行不会被改变，若上2行不同色说明这种情况解不出
                break;
            }
            if(i==15 && ((tempBoard & 0x00ffff00) == 0 || (tempBoard & 0x00ffff00) == 0x00ffff00)){
                solved=1;
            }
        }
        if(solved==1 && flipTimes<minFlip){
            minFlip=flipTimes;
        }
    }
    if(minFlip==17){
        printf("Impossible");
    }else{
        printf("%d", minFlip);
    }

    return 0;
}