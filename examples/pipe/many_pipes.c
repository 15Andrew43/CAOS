#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h>

// gcc -std=c99 many_pipes.c -o many_pipes && ./many_pipes ./a.sh cat cat cat cat ./c.sh ./b.sh

int main(int argc, char *argv[]) {

    int n = argc - 1; // 2

    int n_pipes = n - 1; // 1

    int* pipes = (int *)calloc(2 * n_pipes, sizeof(int));


    pipe(pipes);
    pid_t pid = fork();

    if (0 == pid) {
        close(pipes[0]);

        dup2(pipes[1], 1);
        close(pipes[1]);

        execlp(argv[1], argv[1], NULL);
    }
    waitpid(pid, 0, 0);

    for (int i = 1; i < n - 1; ++i) {
        pipe(pipes + 2 * i);

        pid_t pid2 = fork();

        if (0 == pid2)  {
            close(pipes[2 * i - 1]);
            close(pipes[2 * i]);

            dup2(pipes[2 * (i - 1)], 0);
            close(pipes[2 * (i - 1)]);

            dup2(pipes[2 * i + 1], 1);
            close(pipes[2 * i + 1]);

            execlp(argv[i + 1], argv[i + 1], NULL);
        } else {
            close(pipes[2 * i - 1]);
            close(pipes[2 * i - 2]);
            waitpid(pid2, 0, 0);
        }

    }

    pid_t pid3 = fork();

    if (0 == pid3) {
        close(pipes[2 * n_pipes - 1]);

        dup2(pipes[2 * n_pipes - 2], 0);
        close(pipes[2 * n_pipes - 2]);

        execlp(argv[n], argv[n], NULL);
    }
    close(pipes[2 * n_pipes - 1]);
    close(pipes[2 * n_pipes - 2]);
    waitpid(pid3, 0, 0);

    free(pipes);
    return 0;   
}
