
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    if(argc < 3){
        perror("Correct usage : ./p2 <num1> <num2>");
        exit(1);
    }

    printf("child pid before exec : %d\n",getpid());
    printf("parent pid before exec: %d\n",getppid());

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    int sum = n1 + n2;
    printf("Sum : %d\n",sum);

    return 0;
}