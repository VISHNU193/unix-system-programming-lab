// main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    char *env_init[] = {
        "USER=custom_user",
        "PATH=/custom_path",
        "LANG=en_CUSTOM",
        NULL
    };

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    }

    if (pid == 0) {

        printf("\n[Child] Executing echoall with custom environment:\n");
        if (execle("./echoall", "echoall", "arg1", "arg2", (char *)0, env_init) < 0) {
            perror("execle error");
            exit(1);
        }
    } else {

        if (waitpid(pid, NULL, 0) < 0) {
            perror("wait error");
            exit(1);
        }

        printf("\n[Parent] Executing echoall with default environment:\n");
        if (execlp("./echoall", "echoall", "default_arg", (char *)0) < 0) {
            perror("execlp error");
            exit(1);
        }
    }

    return 0;
}
