#include <sys/types.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <stdio.h>

#include <string.h>


#include <sys/mman.h>

#include <stdlib.h>


int
main(int argc, char *argv[])
{

    int in = open(argv[1], O_RDONLY);

    struct stat st;
    fstat(in, &st);
    if (0==st.st_size) {
        close(in);
        exit(0);
    }

    int *contents = mmap(NULL,
                          st.st_size,
						  PROT_READ,
                          MAP_PRIVATE,
                          in,
                          0);

    // printf("%d\n", *contents);
    // printf("%d\n", *(contents+1));
    // printf("%d\n", *(contents+2));
    // printf("%d\n", *(contents+3));

    int value;
    u_int32_t next_pointer = 1;
    int* ptr = contents;

    while (next_pointer != 0) {
    	value = *ptr;
    	printf("%d\n", value);
        next_pointer = *(ptr+1);
        ptr = contents + next_pointer/sizeof(int);
    }


    close(in);
    munmap(contents, st.st_size);
    return 0;
}