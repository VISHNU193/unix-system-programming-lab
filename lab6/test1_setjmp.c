#include <stdio.h>
#include <setjmp.h>

jmp_buf jump_buffer;

void second() {
    printf("In second function. Now jumping back using longjmp...\n");
    longjmp(jump_buffer, 42);  // Jump back to where setjmp was called
}

void first() {
    second();
    printf("This won't be printed because of longjmp.\n");
}

int main() {
    int val = setjmp(jump_buffer);

    if (val == 0) {
        printf("setjmp returned 0, calling first()...\n");
        first();
    } else if(val==42){
        printf("Back in main, longjmp returned us here with value: %d\n", val);
    }

    return 0;
}