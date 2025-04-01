#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc , char *argv[]){

    struct dirent *dirent;
    struct stat file_stat;
    DIR *dp;

    dp = opendir(".");

    if(dp){
        printf("inode mode uid gid access_time filename \n ");

        while(dirent = readdir(dp)){
            stat(dirent->d_name,&file_stat);
            printf("%ld %d %d %d %s %s \n",file_stat.st_ino,file_stat.st_mode, file_stat.st_uid, file_stat.st_gid, ctime(&file_stat.st_atime), dirent->d_name);
        }
    }

    return 0;
}