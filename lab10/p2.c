// #include <stdio.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <unistd.h>
// int main(int argc, char *argv[])
// {
//     int fd;
//     char buf[255];
//     struct flock fv;
//     if (argc < 2)
//     {
//         printf("usage %s <filename>\n", argv[0]);
//         exit(0);
//     }
//     if ((fd = open(argv[1], O_RDWR)) == -1)
//     {
//         printf("error\n");
//         exit(1);
//     }
//     fv.l_type = F_WRLCK;
//     fv.l_whence = SEEK_END;
//     fv.l_start = SEEK_END - 100;
//     fv.l_len = 100;
//     printf("press enter to set lock\n");
//     getchar();
//     printf("trying to get lock\n");
//     if ((fcntl(fd, F_SETLK, &fv)) == -1)
//     {
//         fcntl(fd, F_GETLK, &fv);
//         printf("file is locked by process pid: %d \n", fv.l_pid);
//         return -1;
//     }
//     printf("locked\n");
//     if ((lseek(fd, SEEK_END - 50, SEEK_END)) == -1)
//     {
//         printf("lseek\n");
//         exit(1);
//     }
//     if ((read(fd, buf, 100)) == -1)
//     {
//         printf("read\n");
//         exit(1);
//     }
//     printf("data from file:\n");
//     puts(buf);
//     printf("press enter to unlock\n");
//     getchar();
//     fv.l_type = F_UNLCK;
//     fv.l_whence = SEEK_SET;
//     fv.l_start = 0;
//     fv.l_len = 0;
//     if ((fcntl(fd, F_UNLCK, &fv)) == -1)
//     {
//         printf("error\n");
//         exit(0);
//     }
//     printf("unlocked\n");
//     close(fd);
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    char buf[256];  // Increased by 1 for null-termination
    struct flock fv;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Set write lock
    fv.l_type = F_WRLCK;
    fv.l_whence = SEEK_END;
    fv.l_start = -100; // Lock last 100 bytes
    fv.l_len = 100;

    printf("Press Enter to set lock...\n");
    getchar();

    printf("Trying to acquire lock...\n");
    if (fcntl(fd, F_SETLK, &fv) == -1)
    {
        perror("Lock failed");
        fcntl(fd, F_GETLK, &fv);
        if (fv.l_type != F_UNLCK)
        {
            printf("File is locked by process PID: %d\n", fv.l_pid);
        }
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Lock acquired.\n");

    // Move to the correct position and read
    if (lseek(fd, -50, SEEK_END) == -1)
    {
        perror("lseek failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    ssize_t bytesRead = read(fd, buf, 100);
    if (bytesRead == -1)
    {
        perror("Read failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    buf[(bytesRead < 255) ? bytesRead : 255] = '\0';  // Ensure null termination
    printf("Data from file:\n%s\n", buf);

    printf("Press Enter to unlock...\n");
    getchar();

    // Unlock the file
    fv.l_type = F_UNLCK;
    fv.l_whence = SEEK_END;
    fv.l_start = -100;
    fv.l_len = 100;

    if (fcntl(fd, F_SETLK, &fv) == -1)
    {
        perror("Unlock failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("File unlocked.\n");

    close(fd);
    return 0;
}
