// echoall.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
    int i;


    printf("\n----- Environment Variables -----\n");
    for (i = 0; i<5; i++) {
        printf("envp[%d] = %s\n", i, envp[i]);
    }

    return 0;
}
