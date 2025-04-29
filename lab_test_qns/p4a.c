// Write a program to copy access and modification time of a file to another file using utime function.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>


int main(int argc,char *argv[]){
    struct stat file1_info;
    struct stat file2_info;
    struct utimbuf time_buf;


    if(stat(argv[1], &file1_info)<0){
        printf("Error getting info of file %s \n",argv[1]);
        exit(1);
    }

    if(stat(argv[2], &file2_info) < 0){
        printf("Error getting info of file %s \n",argv[2]);
        exit(1);
    }


    printf("Before copying : \n");
    printf("Last access time  : %s\n",ctime(&file1_info.st_atime));
    printf("Last modfied time : %s\n",ctime(&file1_info.st_mtime));


    time_buf.actime = file2_info.st_atime;
    time_buf.modtime = file2_info.st_mtime;

    if(utime(argv[1], &time_buf)<0){
        printf("Error copying %s time data to %s\n",argv[2],argv[1]);
        exit(1);
    }

    if(stat(argv[1],&file1_info)<0){
        printf("Error accesing file data of %s\n",argv[1]);
        exit(1);
    }


    printf("After copying :\n");
    printf("Last acces time    : %s\n", ctime(&file1_info.st_atime));
    printf("Last modified time : %s\n", ctime(&file1_info.st_mtime));


    return 0;

}
