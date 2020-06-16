#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void write1();
void write2();

int main(int argc, char *argv[]) {
    write1();
    write2();
    return 0;
}

/**
 * 第一次open文件时截断 O_TRUNC 了，所以文件被清空
 * 在第二次写文件时，不能 O_APPEND 的方法写入
 **/
void write1() {
    FILE *f = fopen("catalina.log", "w+");
    if (f == NULL) {
        perror("OPEN file error: catalina.log");
        printf("errorno: %d\n", errno);
    }

    fclose(f);

    f = fopen("catalina.log", "a+");
    if (f == NULL) {
        exit(1);
    }
    int n = fputs("2222测试\n", f);
    printf("write catalina.log  %d \n", n);
    fclose(f);
}

/**
 * append 写入是从文件头开始写，后写先出 ^-^
 * 需要fclose flush到文件中并以 null 结束，如果没有flush，则下次写会从头部开始写
 **/
void write2() {
    FILE *f = fopen("catalina.log", "a+");
    if (f == NULL) {
        perror("OPEN file catalina.log error");
        exit(1);
    }
    printf("当前文件位置 %ld \n", ftell(f));
    
    fputs("append write\n", f);
    fputs("append write 2 \n", f);
    fclose(f);
}