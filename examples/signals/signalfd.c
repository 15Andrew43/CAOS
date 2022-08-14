#include <stdio.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// how do run?

//terminal 0
// docker build . && docker run -i --rm $(array=($(echo $(docker images -q))); echo ${array[0]})

//terminal 1
// docker rm $(docker ps -aq)
// docker exec -it $(echo $(docker ps -aq)) bash

void read_sigints(int sigfd) {
    struct signalfd_siginfo info;
    while (1) {
        read(sigfd, &info, sizeof(info));
        printf(
            "Received signal %d from process %d in process %d. Additional value passed is %d\n",
            info.ssi_signo,
            info.ssi_pid,
            getpid(),
            info.ssi_int
        );
        fflush(stdout);
        if (info.ssi_signo == SIGTERM) {
            break;
        }
    }
}


int main() {
    printf("\n\n\npep\n\n\n");
    fflush(stdout);
    // FILE* file = open("file.txt", "w");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTERM);

    // block SIGINT  for processing by ordinary handlers
    sigprocmask(SIG_BLOCK, &mask, NULL);
    // open file descriptor
    int sigfd = signalfd(-1, &mask, 0);

    pid_t pid = fork();
    if (pid == 0) {
        printf("Child pid: %d\n\n", getpid());
        fflush(stdout);
        read_sigints(sigfd);
    } else if (pid > 0) {
        printf("Parent pid: %d\n\n", getpid());
        fflush(stdout);
        read_sigints(sigfd);
        waitpid(pid, NULL, 0);
    }
    close(sigfd);
    return 0;
}