// Write a C program to remove empty files from the given directory.

#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>


/*

In the context of file systems, "unlink" removes a file name or a link to a file, potentially leading to the file's deletion if it was the last link and no processes have it open. 


*/
int main(int argc,char *argv[]){
    
    struct stat file_info;
    struct dirent *dir;
    DIR *dp;

    dp = opendir(".");

    if(dp){

        while((dir = readdir(dp)) != NULL){
            stat(dir->d_name, &file_info);

            if(file_info.st_size == 0){
                unlink(dir->d_name);
                printf("Deleted file :  %s \n",dir->d_name);
            }
        }
    }

    return 0;
}