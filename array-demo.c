#include<stdio.h>
main(int argc, char const *argv[])
{
    int a[] = {1, 3, 6, 8, 2, 3, 0};
    int b[7];
    for (int i = 0; i < 7; i++) {
        b[i] = a[i];
    }

    for (int j = 0; j < 7; j++) {
        printf("===> %d \n", b[j]);
    }
    return 0;
}
