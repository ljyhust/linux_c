#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_EVENTS 10

struct epoll_event ev, events[MAX_EVENTS];

int
make_socket_non_blocking (int sfd);

void epoll_net_io() {
    struct sockaddr_in serveraddr, cliaddr;
    int listenfd, nfds, conn_sock;
    int addrlen = sizeof(cliaddr);

    int epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_createl");
        exit(EXIT_FAILURE);
    }

    // 注册监听
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(9060);

    bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
    listen(listenfd, 200);
    printf("start listen....\n");
    
    ev.events = EPOLLIN;
    ev.data.fd = listenfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    while (1) {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (-1 == nfds) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        printf("nfds = %d\n", nfds);
        
        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == listenfd) {
                conn_sock = accept(listenfd, (struct sockaddr *) &cliaddr, &addrlen);
                if (conn_sock == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                printf("new connection\n");
                make_socket_non_blocking(conn_sock);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_sock;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,
                            &ev) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            } else {
                //do_use_fd(events[n].data.fd);
                printf("read fd = %d\n", events[n].data.fd);
            }
        }
    }
    
}

void main() {
    epoll_net_io();
}

int make_socket_non_blocking (int sfd) {
  int flags, s;

  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1) {
      perror ("fcntl");
      return -1;
    }

  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1) {
      perror ("fcntl");
      return -1;
    }

  return 0;
}