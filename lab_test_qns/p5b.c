// Write a program to differentiate between dup and dup2 functions

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd1 = open("sample.txt", O_RDONLY);
    int fd2 = dup(fd1);        // copies to lowest free fd
    int fd3 = dup2(fd1, 10);   // copies to specified fd (10)

    printf("Original fd: %d\n", fd1);
    printf("dup fd: %d\n", fd2);
    printf("dup2 fd (should be 10): %d\n", fd3);

    close(fd1);
    close(fd2);
    close(fd3);
    return 0;
}
