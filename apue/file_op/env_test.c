#include<stdio.h>
#include<stdlib.h>

int main(int argc, char * argv[]) {

    char *listen_backlog = getenv("net.core.somaxconn");
    printf("backlog %s", listen_backlog);
    exit(0);
}