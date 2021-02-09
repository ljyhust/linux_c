#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "chat_common.h"
#include <sys/select.h>

#define MAXLINE 4096

int main(int argc, char *argv[]) {

    int listenfd, connfd;
    socklen_t len;
    struct sockaddr_in serveraddr, cliaddr;
    char buff[MAXLINE];
    struct chat_user users[FD_SETSIZE];
    fd_set rset, allset;
    int maxfd, i, n;
    int maxi = -1;
    int nready;

    // 初始化chat_user
    int k;
    for(k = 0; k < FD_SETSIZE; k++) {
        users[k].connfd = -1;
        users[k].chat_state = -1;
    }
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(9060);

    // 绑定socket和ip port
    bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
    listen(listenfd, 200);
    maxfd = listenfd;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    perror("====== start listen");
    char *str = "please enter user password\n";
    while (1)
    {
        //rset = allset;
        len = sizeof(cliaddr);
        nready = select(maxfd + 1, &allset, NULL, NULL, NULL);
        printf("new listen %d ...\n", nready);
        // 判断是否有新连接
        if (FD_ISSET(listenfd, &allset)) {
            connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
            printf("connected by fd %d\n", connfd);
            for(i = 0; i < FD_SETSIZE; i++) {
                if(users[i].connfd < 0) {
                    users[i].connfd = connfd;
                    users[i].chat_state = -1;
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                perror("too many clients");
                break;
            }
            write(connfd, str, strlen(str));
            FD_SET(connfd, &allset);
            if (connfd > maxfd) {
                maxfd = connfd;
            }

        }

        for (i = 0; i < FD_SETSIZE; i++) {
            if ((connfd = users[i].connfd) < 0) {
                continue;
            }

            if (FD_ISSET(connfd, &allset)) {
                // 读取信息
                if ( (n = read(connfd, buff, MAXLINE)) == 0) {
                    shutdown(connfd, SHUT_RDWR);
                    users[i].connfd = -1;
                    users[i].chat_state = -1;
                    FD_CLR(connfd, &allset);
                } else {
                    // 如果未登录，先判断账密，则write提示登录
                    if (users[i].chat_state < 0) {
                        printf("recv msg %s\n", buff);
                        write(connfd, str, strlen(str));
                        
                    } else {
                        printf("user %d login\n", connfd);
                    }
                }

            }
        }
        //printf("connenct from %s, port %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)), ntohs(cliaddr.sin_port));
              
    }
    
}