// Write a program to demonstrate the zombie state of a process and provide the solution for the same.  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is running...\n", getpid());
        sleep(2);  // Simulate some work
        printf("Child process (PID: %d) is exiting...\n", getpid());
        exit(0);   // Child exits, becomes a zombie
    } else {
        // Parent process (does not wait for child)
        printf("Parent process (PID: %d) continues running...\n", getpid());
        printf("Check 'ps -el | grep Z' to see the zombie process.\n");
        sleep(10);  // Parent sleeps, child remains a zombie
        printf("Parent process exiting...\n");
    }

    return 0;
}