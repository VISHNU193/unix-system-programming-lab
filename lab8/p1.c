// 1.Write a C program to perform the following operations
// i. To create a child process
// ii. The child process should execute a program (using exec( )) to show the
// use of the access function
// iii. The parent process should wait for the child process to exit
// iv. Also print the necessary process IDs

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;
    pid_t parent_pid = getpid();
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        pid_t child_pid = getpid();
        printf("Child process (PID: %d) executing...\n", child_pid);
        execl("./p1_exec", "p1_exec", "example.txt", (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Parent process (PID: %d) executing...\n", parent_pid);
        waitpid(pid, &status, 0);
        printf("Parent process: Child process (PID: %d) has exited.\n", pid);
    }
    return 0;
}