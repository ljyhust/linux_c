#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<time.h>

// 读操作用的数组大小
#define READ_SIZE 4096

char C_BUF[8 * 1024];

// 系统IO读，用4096数组接收读数据
double test_read_system_io(char *filename);
// 标准IO读，用4096数组接收读数据
double test_read_standard_io(char *filename);
// 标准IO读，设置标准IO的缓冲大小为8K，用4096数组接收读数据
double test_read_standard_io_8k(char *filename);
// 标准IO读，按行读数据，标准IO缓冲大小为8K，用4096数组接收读数据
double test_read_standard_io_line(char *filename);

int main(int argc, char *argv[]) {
    test_read_standard_io("/mnt/e/logs/catalina.out");
    test_read_system_io("/mnt/e/logs/catalina.out");
    test_read_standard_io_8k("/mnt/e/logs/catalina.out");
    test_read_standard_io_line("/mnt/e/logs/catalina.out");
}

/**
 * 系统调用read()读，直接从内核态高速缓存读入buf中 
 **/
double test_read_system_io(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (-1 == fd) {
        perror("openfile error");
        exit(1);
    }
    char buf[READ_SIZE];
    int i = 0;
    int sum_iterator = 0;
    int len = sizeof(buf);
    time_t start_time = clock();
    while((i = read(fd, buf, len)) != 0) {
        sum_iterator++;
    }
    
    time_t end_time = clock();

    double diff = difftime(end_time, start_time);
    printf("system io, diff time = %d ms, iterate = %d\n", (int)diff, sum_iterator);
    return diff;
}

/**
 * 标准io读，不设置标准缓冲大小，即采用标准io缓冲大小，见stdio.h中定义BUFSIZE  4Kb
 **/
double test_read_standard_io(char *filename) {
    FILE *fi = fopen(filename, "r");
    if (NULL == fi) {
        perror("openfile error");
        exit(1);
    }

    char buf[READ_SIZE];
    int i;
    int sum_iterator = 0;
    time_t start_time = clock();
    while((fread(buf, READ_SIZE, sizeof(char), fi)) != 0) {
        sum_iterator++;
    }
    
    time_t end_time = clock();
    double diff = difftime(end_time, start_time);

    printf("stardard io, diff time = %d ms, iterate = %d\n", (int)diff, sum_iterator);
    return diff;
}

/**
 * 标准IO，设置IO缓冲区大小为8 * 1024
 */
double test_read_standard_io_8k(char *filename) {
    FILE *fi = fopen(filename, "r");
    if(NULL == fi) {
        perror("open file error");
        exit(1);
    }
    // 设置标准缓冲为全缓冲，缓冲为C_BUF 大小为 8 * 1024
    setvbuf(fi, C_BUF, _IOFBF, sizeof(C_BUF));

    char buf[READ_SIZE];
    int i;
    int sum_iterator = 0;
    time_t start_time = clock();
    //char *temp;
    while((fread(buf, READ_SIZE, sizeof(char), fi)) != 0) {
        sum_iterator++;
    }
    
    time_t end_time = clock();
    double diff = difftime(end_time, start_time);

    printf("8K standard io cache, diff time = %d ms, iterate = %d\n", (int)diff, sum_iterator);
    return diff;
}

/**
 * 使用标准IO按行读取，迭代次数更多，但性能没有降低，且对应用程序操作更方便，尤其是读文件按行读时
 */
double test_read_standard_io_line(char *filename) {
    FILE *fi = fopen(filename, "r");
    if(NULL == fi) {
        perror("open file error");
        exit(1);
    }
    // 设置全缓冲模式
    setvbuf(fi, C_BUF, _IOFBF, sizeof(C_BUF));

    char buf[READ_SIZE];
    int i;
    int sum_iterator = 0;
    time_t start_time = clock();
    while(NULL != fgets(buf, READ_SIZE, fi)) {
        sum_iterator++;
    }
    
    time_t end_time = clock();
    double diff = difftime(end_time, start_time);

    printf("8K standard io fgets, diff time = %d ms, iterate = %d\n", (int)diff, sum_iterator);
    return diff;
}
