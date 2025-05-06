// Write a C program to implement ls  –li command which lists the files in a specified directory. Your program should Print 5 attributes of files.

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    const char *dir_path = (argc > 1) ? argv[1] : ".";
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    struct stat st;
    char path[512];

    while ((entry = readdir(dir)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
        if (stat(path, &st) == 0) {
            printf("Inode: %ld ", (long)st.st_ino);
            printf("Permissions: %o ", st.st_mode & 0777);
            printf("Links: %ld ", (long)st.st_nlink);
            printf("Owner UID: %d ", st.st_uid);
            printf("Size: %ld\n", (long)st.st_size);
        }
    }

    closedir(dir);
    return 0;
}
