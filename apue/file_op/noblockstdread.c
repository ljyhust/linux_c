#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#define MSG_TRY "try again\n"
//非阻塞读取
int main(int argc, char *argv[]) {
    char buf[10];
    int n;
    int flags;
    // 获取文件状态
    flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    // 设置文件状态
    if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1) {
        perror("fcntl set");
        exit(1);
    }
    do {
        n = read(STDIN_FILENO, buf, 10);
        if (n < 0) {
            if (errno == EAGAIN) {
                sleep(1);
                write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
                continue;
            }
            perror("read stdin");
            exit(1);
        } else {
            break;
        }
    } while(1);
    write(STDOUT_FILENO, buf, n);
    return 0;
}