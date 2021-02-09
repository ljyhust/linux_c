#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "SDL2/SDL.h"

volatile sig_atomic_t device_update_flag = 0;

/**
 * 信号处理函数
 */
static void alarm_sig_handler(int signum) {
    //printf("alarm handler %d  flag=%d \n", signum, device_update_flag);
    device_update_flag = 1;
    //printf("alarm handler %d  flag=%d \n", signum, device_update_flag);
}

/* 定时信号处理 */
int main(int argc, char* argv[]) {
    struct sigaction s;
    memset(&s, 0, sizeof(s));
    s.sa_handler = alarm_sig_handler;
    sigaction(SIGVTALRM, &s, NULL);

    struct itimerval it = {};
    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = 1000000 / 6;
    it.it_interval = it.it_value;
    setitimer(ITIMER_VIRTUAL, &it, NULL);
    SDL_Event event;
    int done = 0;
    while (!done)
        while (SDL_PollEvent(&event)) {
            printf("type %x \n", event.type);
            switch (event.type)

                {

                case SDL_KEYDOWN:
                    printf("keydown\n");
                    break;

                case SDL_QUIT:

                    done = 1;

                    break;

                default:

                    break;

                }
            //sleep(0.05);
            //printf("main flag=%d\n", device_update_flag);
            device_update_flag = 0;
        }
    return 0;
}