#include<stdio.h>

int main() {
    __uint64_t a = 0x1;
    __uint64_t b = 0x2;
    __uint64_t c = a - b;
    //__uint8_t c = a + b;
    printf("==== res id %ld\n", c);
    return 0;
}