#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define BUF_SIZE 1024
#define BUF_NUM 3
#define MAX_FULL_PATH 4352

int a = 0, isFinished = 0;
int sFree, sUnWrite;
FILE *in, *out;
typedef struct BufBlock
{
    char buf[BUF_SIZE];
    int size;
} bufBlock;
bufBlock *buffer[BUF_NUM];
int shmIds[BUF_NUM];

union semun {
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO
    (Linux-specific) */
};

void P(int semId)
{
    struct sembuf semCtrler;
    semCtrler.sem_num = 0; // first sem in sem set
    semCtrler.sem_op = -1; // p operation
    semCtrler.sem_flg = 0;
    semop(semId, &semCtrler, 1);
    return;
}

void V(int semId)
{
    struct sembuf semCtrler;
    semCtrler.sem_num = 0; // first sem in sem set
    semCtrler.sem_op = 1;  // v operation
    semCtrler.sem_flg = 0;
    semop(semId, &semCtrler, 1);
    return;
}

void readbuf()
{
    int read = 0; // index of next buffer reading out from
    int res;
    do
    {
        P(sUnWrite); // wait for writebuf to write in
        res = fwrite(buffer[read]->buf, 1, buffer[read]->size, out);
        V(sFree); // allow writebuf to write 1 more buf
        read = (read + 1) % BUF_NUM;
    } while (res == BUF_SIZE);
    fclose(out);
}

void writebuf()
{
    int write = 0; // index of next buffer writing in
    int res;
    do
    {
        P(sFree); // wait for readbuf to read out
        res = fread(buffer[write]->buf, 1, BUF_SIZE, in);
        buffer[write]->size = res;
        V(sUnWrite); // allow readbuf to read 1 more buf
        write = (write + 1) % BUF_NUM;
    } while (res == BUF_SIZE); // if the end of file is a whole block, read another empty block to infrom readbuf that file has ended.
    fclose(in);
}

int main()
{
    pid_t pid1, pid2;
    int result;
    void *p;
    char fIn[MAX_FULL_PATH + 1], fOut[MAX_FULL_PATH + 1];
    sFree = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    sUnWrite = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if (sFree == -1 || sUnWrite == -1)
    {
        puts("error creating semaphores!");
        return 1;
    }

    // initialize semaphores
    union semun semInitVal;
    semInitVal.val = BUF_NUM; // at the beginning all buf room is free
    if (semctl(sFree, 0, SETVAL, semInitVal) == -1)
    {
        puts("error initializing semaphores!");
        return 1;
    }
    semInitVal.val = 0; // at the beginning there's no data to be write
    if (semctl(sUnWrite, 0, SETVAL, semInitVal) == -1)
    {
        puts("error initializing semaphores!");
        return 1;
    }

    // create shared memory buffers
    for (int i = 0; i < BUF_NUM; i++)
    {
        result = shmget(IPC_PRIVATE, sizeof(bufBlock), IPC_CREAT | 0666);
        if (result == -1)
        {
            puts("error creating shared memory!");
            return 1;
        }
        shmIds[i] = result;
        p = shmat(result, NULL, SHM_W | SHM_R);
        if (p == (void *)-1)
        {
            puts("error creating shared memory!");
            return 1;
        }
        buffer[i] = (bufBlock *)p;
    }

    puts("请输入待复制的文件名：");
    scanf("%4352s", fIn);
    puts("请输入复制的新文件名：");
    scanf("%4352s", fOut);
    in = fopen(fIn, "r");
    out = fopen(fOut, "w");
    if (!in)
    {
        printf("error opening input file %s!\n", fIn);
        return 1;
    }
    if (!out)
    {
        printf("error opening output file %s!\n", fOut);
        return 1;
    }

    if ((pid1 = fork()) == 0)
    {
        // sub process readbuf
        readbuf();
    }
    else
    {
        if ((pid2 = fork()) == 0)
        {
            // sub process writebuf
            writebuf();
        }
        else
        {
            // parent process
            wait(NULL);
            wait(NULL);
            for (int i = 0; i < BUF_NUM; i++)
            {
                shmdt(buffer[i]);
                shmctl(shmIds[i], IPC_RMID, NULL);
            }
        }
    }
    return 0;
}