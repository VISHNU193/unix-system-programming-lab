// echoall.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
    int i;

    printf("----- Command-line Arguments -----\n");
    for (i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    printf("\n----- Environment Variables -----\n");
    for (i = 0; i<5; i++) {
        printf("envp[%d] = %s\n", i, envp[i]);
    }

    return 0;
}
