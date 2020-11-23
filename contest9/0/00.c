#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    uint32_t N = strtoul(argv[1], NULL, 10);
    uint32_t i;
    for (i=1; i<=N; ++i) {
        printf("%d ", i);
    }
}