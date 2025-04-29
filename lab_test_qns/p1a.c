// Write a C program to create a child process and show how parent and child processes will share the text file and justify that both parent and child share the same file offset.

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("input.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    char ch;

    for (off_t i = 1; i <= size; i++) {
        lseek(fd, -i, SEEK_END);
        read(fd, &ch, 1);
        write(STDOUT_FILENO, &ch, 1);
    }

    close(fd);
    return 0;
}

