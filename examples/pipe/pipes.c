#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

// gcc -std=c99 pipes.c -o pipes && ./pipes ./a.sh ./b.sh

int main(int argc, char *argv[]) {

    char* cmd1 = argv[1];
    char* cmd2 = argv[2];

    int fd[2];
    pipe(fd);

    pid_t pid1 = fork();

    if (0 == pid1) { // ./a.sh
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        execlp(cmd1, cmd1, NULL);
    } 
    
    pid_t pid2 = fork();

    if (0 == pid2) {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);

        execlp(cmd2, cmd2, NULL);
    }

    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}
