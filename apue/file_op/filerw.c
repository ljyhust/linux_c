#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    char buf[10];
    int n;
    // 读取大于10个字符
    n = read(STDIN_FILENO, buf, 10);
    if (n < 0) {
        perror("read STDIN end");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);
    return 0;
}