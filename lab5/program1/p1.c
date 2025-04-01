#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char *argv[]){

    if(argc==3){
        printf("Hard link : %s and %s \n",argv[1],argv[2]);

        if(link(argv[1],argv[2])<0){
            printf("error creating hard link \n");
        }else{
            printf("hard link successfully created \n");

        }


    }
    else if(argc==4){
        printf("soft link %s and %s \n",argv[1],argv[2]);

        if(symlink(argv[1],argv[2])==0)
            printf("soft link created successfully \n");
        else 
            printf("error creating soft link\n");
    }

    return 0;
}