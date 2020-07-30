#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define DEF_PAGER "/bin/more"
#define MAXLINE 2048

int main(int argc, char *argv[]) {
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[MAXLINE];
    FILE *fp;

    // 判断输入
    if (argc != 2) {
        perror("usage: a.out <pathname>");
        exit(1);
    }
    // 打开文件
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("can't open %s", argv[1]);
        exit(1);
    }

    // 建立pipe
    if (pipe(fd) < 0) {
        perror("pipe error");
        exit(1);
    }

    // fork子进程
    if ((pid = fork()) < 0) {
        perror("error fork");
        exit(1);
    }
    // 父进程
    if (pid > 0) {
        //关闭读fd
        close(fd[0]);

        while (fgets(line, MAXLINE, fp) != NULL) {
            n = strlen(line);
            if (write(fd[1], line, n) != n) {
                perror("write error");
                exit(1);
            }
        }
        if (ferror(fp)) {
            perror("fget error");
            exit(1);
        }
        close(fd[1]);

        printf("wait child process stop %d\n", pid);
        if (waitpid(pid, NULL, 0) < 0) {
            perror("waitpid error");
            exit(1);
        }
        printf("child process is closed\n");
        exit(0);
    } else {  //子进程
        // 关闭写
        close(fd[1]);
        printf("pipe fd[0] is %d\n", fd[0]);
        // 复制fd到标准输入
        if (fd[0] != STDIN_FILENO) {
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
                perror("dup2 error");
                exit(1);
            }
            close(fd[0]);
        }

        if ((pager = getenv("PAGER")) == NULL) {
            pager = DEF_PAGER;
        }
        if ((argv0 = strrchr(pager, '/')) != NULL) {
            argv0++;
        } else {
            argv0 = pager;
        }
        printf("argv0 is %s\n", argv0);

        if (execl(pager, argv0, (char *)0) < 0) {
            printf("excel error for %s\n", pager);
            exit(1);
        }
    }
    exit(0);
}