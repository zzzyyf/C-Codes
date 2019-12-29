#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <pthread.h>

int a=0, isFinished=0;
int s1, s2; 
// s1 is used to assure that p1 has produced a new result 
// s2 is used to assure that p2 has finished output

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
    (Linux-specific) */
};

void P(int semId){
    struct sembuf semCtrler;
    semCtrler.sem_num=0; // first sem in sem set
    semCtrler.sem_op=-1; // p operation
    semCtrler.sem_flg=0;
    semop(semId, &semCtrler, 1);
    return;
}

void V(int semId){
    struct sembuf semCtrler;
    semCtrler.sem_num=0; // first sem in sem set
    semCtrler.sem_op=1; // p operation
    semCtrler.sem_flg=0;
    semop(semId, &semCtrler, 1);
    return;
}

void *p1(void *arg){
    for(int i=1;i<101;i++){
        P(s2); // wait for p2 to complete output
        a+=i;
        if(i==100){
            isFinished=1;
        }
        V(s1); // allow p2 to access a
    }
    return NULL;
}

void *p2(void *arg){
    do{
        P(s1); // wait for p1 to complete adding
        printf("%d\n", a);
        if(isFinished==1){
            V(s2);
            return NULL;
        }
        V(s2); // allow p1 to write a
    }while(1);
    return NULL;
}

int main(){
    pthread_t tid1, tid2;
    int result;
    s1 = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
    s2 = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
    if(s1==-1 || s2==-1){
        puts("error creating semaphores!");
        return 0;
    }

    // initialize semaphores
    union semun semInitVal;
    semInitVal.val = 0; // p1 doesn't have any result at the beginning
    result = semctl(s1, 0, SETVAL, semInitVal); 
    if(result==-1){
        puts("error initializing semaphores!");
        return 0;
    }
    semInitVal.val = 1; // p2 "finished" output at the beginning
    result = semctl(s2, 0, SETVAL, semInitVal);
    if(result==-1){
        puts("error initializing semaphores!");
        return 0;
    }
    
    // create threads
    result = pthread_create(&tid1, NULL, p1, NULL);
    if(result!=0){
        puts("error creating threads!");
        return 0;
    }
    result = pthread_create(&tid2, NULL, p2, NULL);
    if(result!=0){
        puts("error creating threads!");
        return 0;
    }
    pthread_join(tid2, NULL);

    return 0;
}