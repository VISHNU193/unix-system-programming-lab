#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("error\n");
    }
    else if (pid == 0)
    {
        if (execl("./textinterpreter", "textinterpreter", "myarg1", "myarg2", "myarg4",( char*)0) < 0)
            printf("error exec\n");
        if (waitpid(pid, NULL, 0) < 0)
            printf("error wait\n");
    }
    return 0;
}