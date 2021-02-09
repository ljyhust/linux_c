// 实现远程文件服务器功能
// 协议采用http，只读取Http URI
// 查看目录和下载：如果是目录，则显示所有目录名；如果是文件，则response byte
#include<stdio.h>
#define _GNU_SOURCE
#include<sys/mman.h>

//char* ll_path(char* path);

int main(int argc, char* argv[]) {
    // 创建socket
    // 绑定socket port
    // 注册要关注的fd
    // select fd
    // select 可读可写的fd
    int pmem_d = memfd_create("pmemd", 0);
    printf("fd is %d\n", pmem_d);
}