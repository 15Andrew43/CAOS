#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


static void* thread_func(void* arg) {
    int ar = (int) arg;
    printf("read bruh_pep = %d from thread %d\n", ar, pthread_self());
    int value;
    /////////////////////////////////////////////////////////////////////////////////////
    scanf("%d", &value);
    printf("read %d from thread %d\n", value, pthread_self());
    // sched_yield();
    scanf("%d", &value);
    printf("read %d from thread %d\n", value, pthread_self());
    //////////////////////////////////////////////////////////////////////////////////////
    return NULL;
}

int main() {
    printf("my pid = %d\n", getpid());
    int bruh_pep = 1543;
    pthread_t thread[5];
    for (int i = 0; i < 2; ++i) {
        pthread_create(&thread[i], NULL, thread_func, (void*) 1543); // the struct can be in args: (void *) &StucturE
    }
    for (int i = 0; i < 2; ++i) {
        pthread_join(thread[i], NULL);
    }
    return 0;
}