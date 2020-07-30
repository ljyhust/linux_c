#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int globvar = 6;
char buf[] = "a write to stdout\n";
int main(int argc, char * argv[]) {
    int var;
    pid_t pid;

    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        perror("error");
        exit(0);
    }

    printf("before fork pid is %d \n", getpid());

    if((pid = fork()) < 0) {
        perror("error");
        exit(0);
    } else if (pid == 0) {
        globvar++;
        var++;
    } else {
        sleep(4);
    }
    printf("this process id is %ld \n", (long)getpid());
    printf("pid = %ld, globvar = %d, var = %d\n", (long)getpid(), globvar, var);
    return 0;

}
