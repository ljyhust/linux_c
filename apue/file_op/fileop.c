#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(int argc, char const *argv[])
{
    /* open file */
    int fd = openat(AT_FDCWD, "test.log", O_RDWR);
    printf("test open %d \n", fd);
    // 如果不关闭，则以下创建fd = 4
    close(fd);
    fd = openat(AT_FDCWD, "test.log", O_APPEND);
    printf("test open %d \n", fd);

    fd = openat(AT_FDCWD, "akae.txt", O_TRUNC);
    printf("test open akae.txt  %d \n", fd);

    int res = fcntl(fd, F_GETFL);
    printf("test open akae.txt  %d \n", res);

    int chres = fcntl(fd, F_SETFL, res &~S_IXOTH &~S_IXUSR &~S_IXGRP);
    printf("test open akae.txt  %d \n", chres);

    //printf("test open akae.txt  %d \n", openat(AT_FDCWD, "akae.txt", O_WRONLY));

    //chres = fchmod(fd, ~S_IXOTH & ~S_IXUSR & ~S_IXGRP);

    //printf("test open akae.txt  %d \n", chres);

    close(fd);

    // 用路径改变权限
    //chres = fchmodat(AT_FDCWD, "akae.txt", S_IWUSR, 0);
    //printf("test open akae.txt  %d \n", chres);

    
    return 0;
}
