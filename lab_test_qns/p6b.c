// b) Write a C program
// i. To read the first 20 characters from a file
// ii. seek to 10th byte from the beginning and display 20 characters from there
// iii. seek 10 bytes ahead from the current file offset and display 20 characters
// iv. Display the file size

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void display(int fd, int count) {
    char buf[1024];
    int r = read(fd, buf, count);
    write(STDOUT_FILENO, buf, r);
    printf("\n");
}

int main() {
    int fd = open("input.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // i. Read first 20 characters
    printf("First 20 characters:\n");
    lseek(fd, 0, SEEK_SET);
    display(fd, 20);

    // ii. Seek to 10th byte and read 20 chars
    printf("From 10th byte (absolute):\n");
    lseek(fd, 10, SEEK_SET);
    display(fd, 20);

    // iii. Seek 10 ahead from current
    printf("10 bytes ahead from current offset:\n");
    lseek(fd, 10, SEEK_CUR);
    display(fd, 20);

    // iv. File size
    struct stat st;
    stat("input.txt", &st);
    printf("File size: %ld bytes\n", (long)st.st_size);

    close(fd);
    return 0;
}
