// Write a program to read n characters from a file and append them back to the same file using dup2 function.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("sample.txt", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    int n;
    printf("Enter number of characters to read and append: ");
    scanf("%d", &n);

    char buffer[n];
    read(fd, buffer, n);

    int newfd = dup2(fd, 1); // redirect stdout to file
    lseek(fd, 0, SEEK_END);  // move to end for appending
    write(newfd, buffer, n); // append content

    close(fd);
    return 0;
}
