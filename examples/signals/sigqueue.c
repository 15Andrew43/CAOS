#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>



int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "too few arguements\n");
        exit(1);
    }

    pid_t reciever = atoi(argv[1]);
    union sigval value;
    int signal_index = (argc >= 3) ? (SIGRTMIN + atoi(argv[2])) : SIGINT;
    value.sival_int = (argc >= 4) ? atoi(argv[3]) : 42;

    printf(
        "My pid is %d. Sending signal %d tp process %d with additional value %d\n",
        getpid(),
        signal_index,
        reciever,
        value.sival_int
    );

    int status = sigqueue(reciever, signal_index, value);
    if (status == -1) {
        perror("sigqueue");
    }
    
}