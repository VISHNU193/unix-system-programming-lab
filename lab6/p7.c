#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void print_exit_status(int status) {
    if (WIFEXITED(status)) {
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal termination, signal number = %d (%s)\n", 
               WTERMSIG(status), strsignal(WTERMSIG(status)));
    } else if (WIFSTOPPED(status)) {
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}

int main(void) {
    pid_t pid;
    int status;
    
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        exit(1);
    } else if (pid == 0) { /* child */
        exit(7);
    }

    if (wait(&status) != pid) { /* wait for child */
        fprintf(stderr, "wait error: %s\n", strerror(errno));
        exit(1);
    }
    print_exit_status(status); /* and print its status */

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        exit(1);
    } else if (pid == 0) { /* child */
        abort(); /* generates SIGABRT */
    }

    if (wait(&status) != pid) { /* wait for child */
        fprintf(stderr, "wait error: %s\n", strerror(errno));
        exit(1);
    }
    print_exit_status(status); /* and print its status */

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        exit(1);
    } else if (pid == 0) { /* child */
        status /= 0; /* divide by 0 generates SIGFPE */
    }

    if (wait(&status) != pid) { /* wait for child */
        fprintf(stderr, "wait error: %s\n", strerror(errno));
        exit(1);
    }
    print_exit_status(status); /* and print its status */
    
    exit(0);
}