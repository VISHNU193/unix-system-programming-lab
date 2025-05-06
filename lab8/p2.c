// 2.Write a program to perform the following operations
// i) To create a child process
// ii) The child process should execute a separate program (using exec
// function) that calculates the addition of two numbers by passing two
// integer values.
// iii) The parent process should wait for a child to complete


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc,char* argv[]){

    if(argc < 3){
        perror("Correct usage : ./p2 <num1> <num2>");
        exit(1);
    }
    pid_t pid = fork();
    if(pid<0){
        perror("fork error");
        exit(1);
    }
    else if(pid == 0){
        printf("child pid before exec : %d\n",getpid());
        printf("parent pid before exec: %d\n",getppid());
        if(execl("./p2_exec","p2_exec",argv[1],argv[2],NULL)<0)
            perror("exec error");
        
    }else{
        waitpid(pid,NULL,0);

    }
    return 0;
}