#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct foo {
    int a, b, c, d;
};

void printfoo(const char *s, const struct foo *p) {
    printf("%s", s);
    printf(" structure at 0x%lx\n", (unsigned long) p);
    printf(" foo.a = %d\n", p->a);
    printf(" foo.b = %d\n", p->b);
    printf(" foo.c = %d\n", p->c);
    printf(" foo.d = %d\n", p->d);
}

void * thr_fn1(void *arg) {
    // malloc替代，用于堆共享
    struct foo *res = malloc(sizeof(struct foo));
    res->a = 1;
    res->b = 2;
    res->c = 3;
    res->d = 4;
    //struct foo  fooarg = {1, 2, 3, 4};
    printfoo("thread 1: \n", res);
    pthread_exit((void *)res);
}

void * thr_fn2(void *arg) {
    printf("thread 2: ID is %lu\n", (unsigned long) pthread_self());
    pthread_exit((void *)0);
}

int main(int argc, char *argv[]) {
    int err; 
    pthread_t tid1, tid2;
    struct foo *fp;
    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0) {
        perror("can't create thread 1");
        exit(0);
    }
    // 等待线程1执行完毕
    pthread_join(tid1, (void *) &fp);
    if (err != 0) {
        perror("can't join with thread 1\n");
        exit(0);
    }
    sleep(1);
    printf("parent starting second thread\n");
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0) {
        perror("can't create thread 2");
        exit(0);
    }
    sleep(2);
    printfoo("parent: \n", fp);
    free(fp);
    exit(0);
}