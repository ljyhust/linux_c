#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_usr(int);
int main(int argc, char *argv[]) {
    if(signal(SIGUSR1, sig_usr) == SIG_ERR) {
        perror("can't catch SIGUR1");
        exit(0);
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        perror("can't catch SIGUSR2");
        exit(0);
    }
    if (signal(SIGHUP, sig_usr) == SIG_ERR) {
        perror("can't catch SIGHUP");
        exit(0);
    }
    if (signal(SIGTERM, sig_usr) == SIG_ERR) {
        perror("can't catch SIGTERM");
        exit(0);
    }
    setbuf(stdout, NULL);
    printf("==== pause for waiting sign\n");
    for(;;) {
        pause();
    }
}

void sig_usr(int signo) {
    if (signo == SIGUSR1) {
        printf("receive SIGUSR1\n");
    } else if(signo == SIGUSR2) {
        printf("receive SIGUSR2\n");
    } else {
        printf("receive signal %d\n", signo);
        exit(0);
    }
}