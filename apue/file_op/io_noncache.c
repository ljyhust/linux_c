#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
    int i;
    for(i = 0; i< 10; i++) {

    char *temp = "kkkttt";
    write(STDOUT_FILENO, temp, sizeof(temp));
    sleep(1);
    }
    printf("\n");
    for (i = 0; i< 10; i++) {

    printf("kkkttt");
    sleep(1);
    }
    
}