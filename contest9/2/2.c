#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define MAX_LEN 4096


int main(int argc, char *argv[])
{
    char word[MAX_LEN];
    int cnt = 0;
    pid_t pid;

    if (scanf("%s", word) == EOF) {
        printf("%d\n", cnt);
        return 0;
    }
    ++cnt;

    pid = fork();
    if (pid > 0) {
        waitpid(pid, &cnt, 0);
        cnt = WEXITSTATUS(cnt);   
    }
      
    while (pid == 0 && scanf("%s", word) != EOF) {
        ++cnt;
        pid_t pid = fork();
        if (pid > 0) {
            waitpid(pid, &cnt, 0);
            cnt = WEXITSTATUS(cnt);
            exit(cnt);
        }
    }
    if (pid == 0) {
        exit(cnt);
    } else {
        printf("%d\n", cnt);
        return 0;
    }
}