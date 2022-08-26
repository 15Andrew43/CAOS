#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// numbers into stdin; threads printf numbers in reverse order

static void* thread_func(void* arg) {
    int value;
    if (scanf("%d", &value) != 1) {
        return NULL;
    }
    pthread_t nexrt_thread;
    pthread_create(&nexrt_thread, NULL, thread_func, 0);
    pthread_join(nexrt_thread, NULL);
    printf("%d\n", value);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, 0);
    pthread_join(thread, NULL);
    return 0;
}