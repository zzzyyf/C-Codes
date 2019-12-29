#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int funcP1(int pipeOut);
int funcP2(int pipeIn);
void sigHandler(int signal);

struct sigaction act;

int main(){
    int p1, p2, r, pgid;
    int pipefd[2];
    setpgid(getpid(), getpid()); // set parent process to group leader
    pgid = getpgrp();
    act.sa_handler = sigHandler;

    r=pipe(pipefd);
    if(r!=0){
        printf("error creating pipe.");
        return 1;
    }

    p1 = fork(); // both parent and sub process continue here
    if(p1==0){ 
        // sub process p1 starts here
        setpgid(getpid(), pgid); // join the process group
        funcP1(pipefd[1]);
    }else{
        // only parent process execute this block
        p2 = fork();
        if(p2==0){ 
            // sub process p2 starts here
            setpgid(getpid(), pgid); // join the process group
            funcP2(pipefd[0]);
        }else{
            // only parent process execute this block
            // catch interrupt signal from keyboard
            sigaction(SIGINT, &act, 0);
            signal(SIGCONT, SIG_IGN);
            signal(SIGALRM, SIG_IGN);
            // wait for the end of two process
            wait(0);
            wait(0);
            // and kill two subprocess
            // and kill itself
            close(pipefd[0]);
            close(pipefd[1]);
            puts("Parent Process is Killed!");
            exit(0);
        }
    }
    return 0;
}

int funcP1(int pipeOut){
    char msg[30];
    int cnt = 0, len;
    signal(SIGINT, SIG_IGN);
    signal(SIGCONT, SIG_IGN);
    sigaction(SIGALRM, &act, 0);
    while(1){
        len = sprintf(msg, "I send you %d times.\n", ++cnt);
        msg[len]='\0';
        write(pipeOut, msg, strlen(msg)+1);
        sleep(1);
    }
}

int funcP2(int pipeIn){
    char msg[30];
    int cnt = 0, len;
    signal(SIGINT, SIG_IGN);
    signal(SIGALRM, SIG_IGN);
    sigaction(SIGCONT, &act, 0);
    while(1){
        read(pipeIn, msg, sizeof msg);
        printf("%s", msg);
    }
}

void sigHandler(int signal){
    switch (signal)
    {
    case SIGALRM:
        // kill p1
        puts("Child Process 1 is Killed by Parent!");
        exit(0);
        break;
    case SIGCONT:
        // kill p2
        puts("Child Process 2 is Killed by Parent!");
        exit(0);
        break;
    case SIGINT:
        kill(0, SIGALRM); // kill p1
        kill(0, SIGCONT); // kill p2
    default:
        break;
    }
}