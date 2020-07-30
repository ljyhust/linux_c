#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

static void my_alarm(int signo) {
    struct passwd *rootptr;

    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL) {
        perror("getpwman(root) error");
        exit(0);
    }
    alarm(1);
}

int main(int argn, char *argv[]) {
    struct passwd *prt;
    
    setbuf(stdout, NULL);
    signal(SIGALRM, my_alarm);

    alarm(1);

    for(; ;) {
        if((prt = getpwnam("jeang")) == NULL) {
            perror("getpwman(jeang) error");
            exit(0);
        }
        if (strcmp(prt->pw_name, "jeang") != 0) {
            printf("return value corrupted!, pw_name = %s\n", prt->pw_name);
        }
    }

}