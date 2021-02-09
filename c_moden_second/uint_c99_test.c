#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    //__uint64_t test_n = -1;
    //void test(__uint64_t n);
    //test(test_n);
    //void testStrTok(char *cmd);
    //char str[] = "cmd   ccc  dddd";
    //testStrTok(str);
    //printf("NULL strtok is %s\n", strtok(NULL, " "));
    //char n_array[] = {'1', '0', '0', '0', '1', '1', '8'};
    //char appen_array[] = {'2', '1'};
    void testAtoI(char *n_str);
    //testAtoI(n_array);
    char hex_str[] = {'0','x','1','2'};
    testAtoI(hex_str);
    //printf("the num is %d\n", testAtoI(hex_str));
}

void test(__uint64_t n) {
    if (n > 0) {
        printf("this unisgn int is %d\n", (int) (n - 1));
    }
}

void testStrTok(char *cmd) {
    char *res = strtok(cmd, " ");
    printf("str split is %s   %s\n", res, cmd);
    char *res2 = strtok(NULL, " ");
    printf("str split is %s   %s\n", res2, cmd);
}

void testAtoI(char *n_str) {
    char *end_p[1] = {};
    printf("the num is %ld\n", strtoul(n_str, &end_p[0], 16));
    printf("the error char is %c\n", *(end_p[0]));
}
